#pragma once
#include<osgViewer/Viewer>
class DrawXXX
{
public:
	DrawXXX();
	~DrawXXX();

	osg::ref_ptr<osg::EllipsoidModel>em;
	osg::Node* createLine(osg::Vec3d start, osg::Vec3d end);
protected:

};