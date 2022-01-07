#pragma once
#include<QObject>
#include<osgEarthDrivers/arcgis/ArcGISOptions>
#include<osgearth/ImageLayer>
#include<QString>
using namespace osgEarth::Drivers;
class Worker :public QObject
{
	Q_OBJECT
public:
	Worker();
private:
	osgEarth::ImageLayer* m_imageLayer;
public slots:
void doWork();

	
signals:
	void resultReady(osgEarth::ImageLayer *layer);
};