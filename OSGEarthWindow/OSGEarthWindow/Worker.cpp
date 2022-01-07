#include"Worker.h"

Worker::Worker()
{
	
}
void Worker::doWork()
{
	osgEarth::Drivers::ArcGISOptions LayerOpt;
	//netImageLayerOpt.url() = osgEarth::URI("https://map.geoq.cn/arcgis/rest/services/ChinaOnlineStreetWarm/MapServer");
	LayerOpt.url() = osgEarth::URI("http://services.arcgisonline.com/ArcGIS/rest/services/Reference/World_Boundaries_and_Places_Alternate/MapServer");
	std::string LayerName = "worldimage1";
	m_imageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(LayerName, LayerOpt));
	emit resultReady(m_imageLayer);
	std::cout << "zzzzzz" << std::endl;
}