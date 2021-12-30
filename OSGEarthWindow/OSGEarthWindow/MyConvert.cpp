#include"MyConvert.h"
#include <osg/MatrixTransform>


MyConvert::MyConvert()
{}
MyConvert::MyConvert(osgViewer::Viewer *viewer) :mViewer(viewer)
{}
MyConvert::~MyConvert()
{}

void MyConvert::setViewer(osgViewer::Viewer * viewer)
{
	mViewer = viewer;
}
// 屏幕坐标转世界坐标
osg::Vec3 MyConvert::ScreenToWorld(const osg::Vec3 screen)
{
	osg::Camera* camera = mViewer->getCamera();
	osg::Matrix VPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Matrix inverseVPW = osg::Matrix::inverse(VPW);
	osg::Vec3d world = screen * inverseVPW;
	return world;
}
// 世界坐标转屏幕坐标
osg::Vec3 MyConvert::WorldToScreen(const osg::Vec3 world)
{
	osg::Camera* camera = mViewer->getCamera();
	osg::Matrix VPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Vec3 screen = world * VPW;
	return screen;
}
// 世界坐标转经纬度
osg::Vec3 MyConvert::WorldToLonLatAlt(const osg::Vec3 world)
{
	osg::EllipsoidModel* em = new osg::EllipsoidModel();
	osg::Vec3d lonLatAlt;
	em->convertXYZToLatLongHeight(world.x(), world.y(), world.z(), lonLatAlt.y(), lonLatAlt.x(), lonLatAlt.z());
	lonLatAlt.x() = osg::RadiansToDegrees(lonLatAlt.x());
	lonLatAlt.y() = osg::RadiansToDegrees(lonLatAlt.y());
	return lonLatAlt;
}
// 经纬度转世界坐标
osg::Vec3 MyConvert::LonLatAltToWorld(const osg::Vec3 lonLatAlt)
{
	osg::Vec3d world;
	osg::EllipsoidModel* em = new osg::EllipsoidModel();
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(lonLatAlt.y()), osg::DegreesToRadians(lonLatAlt.x()), lonLatAlt.z(), world.x(), world.y(), world.z());
	return world;
}
// 屏幕坐标转经纬度
osg::Vec3 MyConvert::ScreenToLonLatAlt(const osg::Vec3 screen)
{
	return WorldToLonLatAlt(ScreenToWorld(screen));
}
// 经纬度转屏幕坐标
osg::Vec3 MyConvert::LonLatAltToScreen(const osg::Vec3 lonLatAlt)
{
	return WorldToScreen(LonLatAltToWorld(lonLatAlt));
}