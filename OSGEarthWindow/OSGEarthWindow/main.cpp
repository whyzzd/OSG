#include "osgearthwindow.h"
#include <QtWidgets/QApplication>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/StateSetManipulator>
#include <osg/Node>
#include <osgFX/Scribe>
#include<Windows.h>
#include<osg/Fog>
#include<osgUtil/SmoothingVisitor>
osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//首先定义四个点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	//v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	//定义颜色数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	//c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
	//设置定点关联方式
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 4));
	//方法一
	//手动定义法线
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	//方法二
	//自动生成法线
	//osgUtil::SmoothingVisitor::smooth(*(geom.get()));//自动生成法线
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
	/*osg::ArgumentParser argument(&argc, argv);*/
    OSGEarthWindow w/*(argument)*/;
    w.show();

	//osg::ArgumentParser argument(&argc, argv);
	//osgViewer::Viewer viewer(argument);
	//osg::Group *root = new osg::Group();
	//osg::Node *m_earthNode = osgDB::readNodeFile("glider.osg");
	//
	//
	///*osgFX::Scribe *sc=new osgFX::Scribe();
	//sc->addChild(m_earthNode);
	//root->addChild(sc);*/
	//
	//viewer.addEventHandler(new osgViewer::StatsHandler());
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	//viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	//root->addChild(m_earthNode);
	//viewer.setSceneData(root);
	//viewer.realize();
	//viewer.run();
	
	//osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	//osg::ref_ptr<osg::Group> gp = new osg::Group;
	//gp->addChild(osgDB::readNodeFile("cow.osg"));

	//osg::ref_ptr<osg::Fog> fog = new osg::Fog;
	//fog->setDensity(0.01);
	//fog->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	//fog->setMode(osg::Fog::LINEAR);  //osg::Fog::EXP  //osg::Fog::EXP2
	//fog->setStart(10);
	//fog->setEnd(50);
	//gp->getOrCreateStateSet()->setAttributeAndModes(fog.get(), osg::StateAttribute::ON);

	//viewer->setSceneData(gp);
	//viewer->run();

	//main中测试绘制面
	/*osgViewer::Viewer viewer;
	osg::Group *root = new osg::Group();
	root->addChild(createQuad().get());
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();*/
	

    return a.exec();
}
