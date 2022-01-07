#include"XYZExSource.h"

XYZExSource::XYZExSource(const TileSourceOptions& options) :TileSource(options), _options(options), _rotate_iter(0u), _rotateStart(0), _rotateEnd(0)
{

}

Status XYZExSource::initialize(const osgDB::Options* dbOptions)
{
	_dbOptions = Registry::instance()->cloneOrCreateOptions(dbOptions);
	if (_options.url().isSet())
	{
		/*_index = TileIndex::load(_options.url()->full());
		if (_index.valid())
		{*/
			setProfile(osgEarth::Registry::instance()->getGlobalGeodeticProfile());
			return STATUS_OK;
		/*}*/
	}
	return Status::Error("Failed to load TileIndex");

}

osg::HeightField* XYZExSource::createHeightField(const TileKey& key, ProgressCallback* progress)
{
	// MapBox encoded elevation PNG.
	// https://www.mapbox.com/blog/terrain-rgb/
	if (1/*_options.elevationEncoding().value() == "mapbox"*/)
	{
		if (getStatus().isError())
			return 0L;

		osg::HeightField *hf = 0;
		osg::ref_ptr<osg::Image> image = createImage(key, progress);
		if (image.valid())
		{
			// Allocate the heightfield.
			hf = new osg::HeightField();
			hf->allocate(image->s(), image->t());

			ImageUtils::PixelReader reader(image.get());
			for (unsigned int c = 0; c < image->s(); c++)
			{
				for (unsigned int r = 0; r < image->t(); r++)
				{
					osg::Vec4 pixel = reader(c, r);
					pixel.r() *= 255.0;
					pixel.g() *= 255.0;
					pixel.b() *= 255.0;
					float h = -10000.0f + ((pixel.r() * 256.0f * 256.0f + pixel.g() * 256.0f + pixel.b()) * 0.1f);
					hf->setHeight(c, r, h);
				}
			}
		}
		return hf;
	}
	else
	{
		return TileSource::createHeightField(key, progress);
	}
}
osg::Image* XYZExSource::createImage(const TileKey& key, ProgressCallback*  progress)
{
	unsigned x, y;
	key.getTileXY(x, y);

	if (_options.invertY() == true)
	{
		unsigned cols = 0, rows = 0;
		key.getProfile()->getNumTiles(key.getLevelOfDetail(), cols, rows);
		y = rows - y - 1;
	}

	std::string location = _template;

	// support OpenLayers template style:
	replaceIn(location, "${x}", Stringify() << x);
	replaceIn(location, "${y}", Stringify() << y);
	replaceIn(location, "${z}", Stringify() << key.getLevelOfDetail());

	// failing that, legacy osgearth style:
	replaceIn(location, "{x}", Stringify() << x);
	replaceIn(location, "{y}", Stringify() << y);
	replaceIn(location, "{z}", Stringify() << key.getLevelOfDetail());

	std::string cacheKey;

	if (!_rotateChoices.empty())
	{
		cacheKey = location;
		unsigned index = (++_rotate_iter) % _rotateChoices.size();
		replaceIn(location, _rotateString, Stringify() << _rotateChoices[index]);
	}


	URI uri(location, _options.url()->context());
	if (!cacheKey.empty())
	{
		uri.setCacheKey(Cache::makeCacheKey(location, "uri"));
	}

	//OE_TEST << LC << "URI: " << uri.full() << ", key: " << uri.cacheKey() << std::endl;

	return uri.getImage(_dbOptions.get(), progress);
}

