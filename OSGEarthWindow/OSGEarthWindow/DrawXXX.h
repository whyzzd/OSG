#pragma once
#include<osgViewer/Viewer>
class DrawXXX
{
public:
	DrawXXX();
	~DrawXXX();

	//������
	osg::Node* createLine(osg::Vec3d start, osg::Vec3d end);

	//����������
	osg::Node* createTrinangle(/*osg::Vec3Array vec*/);

	osg::Node* createTest(){
		return new osg::Node;
	}
protected:

private:
	osg::ref_ptr<osg::EllipsoidModel>em;
};