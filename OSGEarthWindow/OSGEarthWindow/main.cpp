#include "osgearthwindow.h"
#include <QtWidgets/QApplication>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgParticle/PrecipitationEffect>
#include <osg/Node>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OSGEarthWindow w;
    w.show();

	//osgViewer::Viewer viewer;

	//// 设置雪花类
	//osg::ref_ptr<osgParticle::PrecipitationEffect> precipitationEffect = new osgParticle::PrecipitationEffect;

	//// 设置雪花浓度
	//precipitationEffect->snow(0.5);

	////设置雪花颜色
	//precipitationEffect->setParticleColor(osg::Vec4(1, 1, 1, 1));

	//// 设置风向
	//precipitationEffect->setWind(osg::Vec3(2, 0, 0));

	//osg::Group *root = new osg::Group();

	//// 把雪花加入到场景结点
	//root->addChild(precipitationEffect.get());
	//osg::Node *ceep = osgDB::readNodeFile("cow.osg");
	//root->addChild(ceep);
	//viewer.setSceneData(root);
	//viewer.realize();
	//viewer.run();


    return a.exec();
}
