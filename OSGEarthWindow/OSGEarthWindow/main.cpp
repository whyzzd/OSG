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

	//���ȶ����ĸ���
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	//v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	//c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
	//���ö��������ʽ
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 4));
	//����һ
	//�ֶ����巨��
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	//������
	//�Զ����ɷ���
	//osgUtil::SmoothingVisitor::smooth(*(geom.get()));//�Զ����ɷ���
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}

int main(int argc, char *argv[])
{
	osg::ArgumentParser arguments(&argc, argv);
	arguments.getApplicationUsage()->addCommandLineOption("-m", "Set viewer to MASTER mode, sending view via packets.");
	arguments.getApplicationUsage()->addCommandLineOption("-s", "Set viewer to SLAVE mode, receiving view via packets.");
    QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
    OSGEarthWindow w(arguments);
    w.show();
	
	//test����
	//osg::ArgumentParser argument(&argc, argv);
	//osgViewer::Viewer viewer(argument);
	//osg::Group *root = new osg::Group();
	//osg::Node *m_earthNode = osgDB::readNodeFile("simple.earth");

	///*osgFX::Scribe *sc=new osgFX::Scribe();
	//sc->addChild(m_earthNode);
	//root->addChild(sc);*/

	//viewer.addEventHandler(new osgViewer::StatsHandler());
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	//viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	//root->addChild(m_earthNode);
	//viewer.setSceneData(root);
	//viewer.realize();
	//viewer.run();
	
	
    return a.exec();
}

