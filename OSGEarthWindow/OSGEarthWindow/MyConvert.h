#pragma once
#include <osgViewer/Viewer>
class MyConvert
{
public:

	MyConvert();
	MyConvert(osgViewer::Viewer * viewer);
	~MyConvert();
	void setViewer(osgViewer::Viewer * viewer);

	// ��Ļ����ת��������
	osg::Vec3 ScreenToWorld(const osg::Vec3 screen);
	// ��������ת��Ļ����
	osg::Vec3 WorldToScreen(const osg::Vec3 world);
	// ��������ת��γ��
	osg::Vec3 WorldToLonLatAlt(const osg::Vec3 world);
	// ��γ��ת��������
	osg::Vec3 LonLatAltToWorld(const osg::Vec3 lonLatAlt);
	// ��Ļ����ת��γ��
	osg::Vec3 ScreenToLonLatAlt(const osg::Vec3 screen);
	// ��γ��ת��Ļ����
	osg::Vec3 LonLatAltToScreen(const osg::Vec3 lonLatAlt);

protected:
	osgViewer::Viewer *mViewer;
};