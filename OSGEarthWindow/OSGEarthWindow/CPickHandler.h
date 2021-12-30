#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector> // 新增头文件
#include<qdebug.h>
#include <osg/MatrixTransform>
#include"MyConvert.h"
class CPickHandler : public osgGA::GUIEventHandler {

public:
	CPickHandler(osgViewer::Viewer *viewer); 
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	void pick(float x, float y);
	osg::Vec3 screen2World(float x, float y);
	bool PickObject;
	osg::ref_ptr<osg::MatrixTransform> picked;
	bool lbuttonDown;

protected:
	osgViewer::Viewer *mViewer; // mViewer
	osg::Vec3 mWorld;
	osg::Vec3 mLonLatAlt;
	MyConvert mMyConv;
};