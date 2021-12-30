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
// ��Ļ����ת��������
osg::Vec3 MyConvert::ScreenToWorld(const osg::Vec3 screen)
{
	osg::Camera* camera = mViewer->getCamera();
	osg::Matrix VPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Matrix inverseVPW = osg::Matrix::inverse(VPW);
	osg::Vec3d world = screen * inverseVPW;
	return world;
}
// ��������ת��Ļ����
osg::Vec3 MyConvert::WorldToScreen(const osg::Vec3 world)
{
	osg::Camera* camera = mViewer->getCamera();
	osg::Matrix VPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Vec3 screen = world * VPW;
	return screen;
}
// ��������ת��γ��
osg::Vec3 MyConvert::WorldToLonLatAlt(const osg::Vec3 world)
{
	osg::EllipsoidModel* em = new osg::EllipsoidModel();
	osg::Vec3d lonLatAlt;
	em->convertXYZToLatLongHeight(world.x(), world.y(), world.z(), lonLatAlt.y(), lonLatAlt.x(), lonLatAlt.z());
	lonLatAlt.x() = osg::RadiansToDegrees(lonLatAlt.x());
	lonLatAlt.y() = osg::RadiansToDegrees(lonLatAlt.y());
	return lonLatAlt;
}
// ��γ��ת��������
osg::Vec3 MyConvert::LonLatAltToWorld(const osg::Vec3 lonLatAlt)
{
	osg::Vec3d world;
	osg::EllipsoidModel* em = new osg::EllipsoidModel();
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(lonLatAlt.y()), osg::DegreesToRadians(lonLatAlt.x()), lonLatAlt.z(), world.x(), world.y(), world.z());
	return world;
}
// ��Ļ����ת��γ��
osg::Vec3 MyConvert::ScreenToLonLatAlt(const osg::Vec3 screen)
{
	return WorldToLonLatAlt(ScreenToWorld(screen));
}
// ��γ��ת��Ļ����
osg::Vec3 MyConvert::LonLatAltToScreen(const osg::Vec3 lonLatAlt)
{
	return WorldToScreen(LonLatAltToWorld(lonLatAlt));
}