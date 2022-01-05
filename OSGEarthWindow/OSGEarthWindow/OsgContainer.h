#pragma once
#ifndef OSGCONTAINER_H
#define OSGCONTAINER_H

#include<qopenglwidget.h>
#include<osgViewer/Viewer>
#include<osgEarth/MapNode>
#include<osgEarthUtil/EarthManipulator>

#include <osgParticle/PrecipitationEffect>
#include <osgParticle/FireEffect>
#include<osgParticle/ExplosionEffect>
#include<osgParticle/ExplosionDebrisEffect>
#include<osg/Fog>
class CPickHandler;//无法直接包含,只能提前声明
class QInputEvent;
class OsgContainer :public QOpenGLWidget,public osgViewer::Viewer
{
	Q_OBJECT
public:
	OsgContainer(/*osg::ArgumentParser argument,*/QWidget *parent = 0);
	~OsgContainer();

	bool event(QEvent *event);
	
	void setKeyboardModifiers(QInputEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent *event);
	void moveEvent(QMoveEvent *event);
	void timerEvent(QTimerEvent *);
	osgViewer::Viewer *getOSGViewer()
	{
		return this;
	}

	osg::Group *getRoot()
	{
		return root;
	}
	osgEarth::Util::EarthManipulator*getEM()
	{
		return em;
	}

	//控制特效
	bool createSnow();//雪
	bool createRain();
	void createWu();
	bool createFire();//火
	bool createBoom();//爆炸
	bool crateExplosionDebris();//爆炸碎片

	//星空
	void initSky();

public:
	CPickHandler *mCPickHandler;


protected:
	virtual void paintGL();

private:
	void initEarth();
	void initCowTest();

	osg::ref_ptr<osg::Camera>createCamera(int x, int y, int w, int h);

private:
	osg::ref_ptr<osg::Group>root;
	osg::ref_ptr<osgViewer::GraphicsWindow >window;

	osg::Node* m_earthNode;
	
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;

private:
	//特效节点
	osg::ref_ptr<osgParticle::PrecipitationEffect> mSnowNode;
	osg::ref_ptr<osgParticle::PrecipitationEffect> mRainNode;
	osg::ref_ptr<osg::Fog>mWuNode;
	osg::ref_ptr<osgParticle::FireEffect> mFireNode;
	osg::ref_ptr<osgParticle::ExplosionEffect> mBoomNode;
	
	/*osg::ref_ptr<osgParticle::ExplosionDebrisEffect> mEDEBoomNode;*/

	//特效是否已经存在
	bool mHaveSnow=false;
	bool mHaveRain=false;
	bool mHaveWu=false;
	bool mHaveFire=false;
	bool mHaveBoom=false;

public slots:
	//特效槽函数
	void slotSnow(int state);
	void slotRain(int state);
	void slotWu(int state);
	void slotFire(int state);
	void slotBoom(int state);

};

#endif // OSGCONTAINER_H