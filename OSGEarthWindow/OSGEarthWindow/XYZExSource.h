#include <osgEarth/TileSource>
#include <osgEarth/FileUtils>
#include <osgEarth/Registry>
#include <osgEarth/ImageUtils>
#include <osgEarth/URI>

#include <osgEarthUtil/TileIndex>


#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/ImageOptions>

#include <sstream>
#include <stdlib.h>
#include <memory.h>

#include <osgEarthDrivers/gdal/GDALOptions>
//#include "TileIndexOptions"
//#include<osgEarthDrivers/tileindex/TileIndexOptions>
#include<osgEarthDrivers/xyz/XYZOptions>
#include<QObject>

#define LC "[TileIndex driver] "
using namespace osgEarth;
using namespace osgEarth::Drivers;


//Œ¥ µœ÷
class XYZExSource : public QObject, public TileSource
{
	Q_OBJECT

public:
	XYZExSource(const TileSourceOptions& options);
	Status initialize(const osgDB::Options* dbOptions);
	osg::Image* createImage(const TileKey& key, ProgressCallback*  progress);
	virtual std::string getExtension() const
	{
		return _format;
	}

	osg::HeightField* createHeightField(const TileKey& key, ProgressCallback* progress);
private:
	const XYZOptions       _options;
	std::string            _format;
	std::string            _template;
	std::string            _rotateChoices;
	std::string            _rotateString;
	std::string::size_type _rotateStart, _rotateEnd;
	OpenThreads::Atomic    _rotate_iter;
	
	//osg::ref_ptr< Unit::TileIndex > _index;
	osg::ref_ptr<osgDB::Options> _dbOptions; 
};
