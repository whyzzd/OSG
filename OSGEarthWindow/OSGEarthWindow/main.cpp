#include "osgearthwindow.h"
#include <QtWidgets/QApplication>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osgFX/Scribe>
#include<Windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OSGEarthWindow w;
    w.show();

	//osgViewer::Viewer viewer;
	//osg::Group *root = new osg::Group();
	//osg::Node *m_earthNode = osgDB::readNodeFile("glider.osg");
	//
	//
	///*osgFX::Scribe *sc=new osgFX::Scribe();
	//sc->addChild(m_earthNode);
	//root->addChild(sc);*/
	//
	//root->addChild(m_earthNode);
	//viewer.setSceneData(root);
	//viewer.realize();
	//viewer.run();
	


    return a.exec();
}
