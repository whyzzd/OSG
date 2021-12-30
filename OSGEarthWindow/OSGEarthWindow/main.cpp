#include "osgearthwindow.h"
#include <QtWidgets/QApplication>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/StateSetManipulator>
#include <osg/Node>
#include <osgFX/Scribe>
#include<Windows.h>
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
	


    return a.exec();
}
//int main()
//{
//	osgViewer::Viewer viewer;
//	osg::Group *root = new osg::Group();
//	osg::Node *m_earthNode = osgDB::readNodeFile("glider.osg");
//	
//	
//	/*osgFX::Scribe *sc=new osgFX::Scribe();
//	sc->addChild(m_earthNode);
//	root->addChild(sc);*/
//	
//	root->addChild(m_earthNode);
//	viewer.setSceneData(root);
//	viewer.realize();
//	
//	return viewer.run();
//}