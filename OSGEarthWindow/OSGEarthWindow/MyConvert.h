#pragma once
#include <osgViewer/Viewer>
class MyConvert
{
public:

	MyConvert();
	MyConvert(osgViewer::Viewer * viewer);
	~MyConvert();
	void setViewer(osgViewer::Viewer * viewer);

	// 屏幕坐标转世界坐标
	osg::Vec3 ScreenToWorld(const osg::Vec3 screen);
	// 世界坐标转屏幕坐标
	osg::Vec3 WorldToScreen(const osg::Vec3 world);
	// 世界坐标转经纬度
	osg::Vec3 WorldToLonLatAlt(const osg::Vec3 world);
	// 经纬度转世界坐标
	osg::Vec3 LonLatAltToWorld(const osg::Vec3 lonLatAlt);
	// 屏幕坐标转经纬度
	osg::Vec3 ScreenToLonLatAlt(const osg::Vec3 screen);
	// 经纬度转屏幕坐标
	osg::Vec3 LonLatAltToScreen(const osg::Vec3 lonLatAlt);

protected:
	osgViewer::Viewer *mViewer;
};