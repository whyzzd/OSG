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
#include<osgEarth/ImageLayer>
#include<QThread>
#include <osgEarthDrivers/arcgis/ArcGISOptions>
#include"Worker.h"
class CPickHandler;//�޷�ֱ�Ӱ���,ֻ����ǰ����
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
		return m_EM;
	}
	osgEarth::Map *getPMap()
	{
		return m_pMap;
	}

	//������Ч
	bool createSnow();//ѩ
	bool createRain();
	void createWu();
	bool createFire();//��
	bool createBoom();//��ը
	bool crateExplosionDebris();//��ը��Ƭ

	//�ǿ�
	void initSky();

public:
	CPickHandler *mCPickHandler;


protected:
	virtual void paintGL();

private:
	//���ļ�����ʽ����
	void initEarth1();
	//��api����ʽ����
	void initEarth2();
	void initCowTest();

	osg::ref_ptr<osg::Camera>createCamera(int x, int y, int w, int h);

private:
	osg::ref_ptr<osg::Group>root;
	osg::ref_ptr<osgViewer::GraphicsWindow >window;

	osg::Node* m_earthNode;
	
	osg::ref_ptr<osgEarth::Util::EarthManipulator> m_EM;
	osg::ref_ptr<osgEarth::Map>m_pMap;
	//����ͼ���
	osg::ref_ptr<osgEarth::ImageLayer>m_netImageLayer;
	bool m_netIsOpen = false;
	QThread workerThread;
	Worker *mWorker=NULL;

	//������,�޶��߳�
	osg::ref_ptr<osgEarth::ImageLayer>netImageLayer;

private:
	//��Ч�ڵ�
	osg::ref_ptr<osgParticle::PrecipitationEffect> mSnowNode;
	osg::ref_ptr<osgParticle::PrecipitationEffect> mRainNode;
	osg::ref_ptr<osg::Fog>mWuNode;
	osg::ref_ptr<osgParticle::FireEffect> mFireNode;
	osg::ref_ptr<osgParticle::ExplosionEffect> mBoomNode;
	
	/*osg::ref_ptr<osgParticle::ExplosionDebrisEffect> mEDEBoomNode;*/

	//��Ч�Ƿ��Ѿ�����
	bool mHaveSnow=false;
	bool mHaveRain=false;
	bool mHaveWu=false;
	bool mHaveFire=false;
	bool mHaveBoom=false;

	//��Ƶ�Ƿ��Ѵ���
	bool mHaveVideo = false;

public slots:
	//��Ч�ۺ���
	void slotSnow(int state);
	void slotRain(int state);
	void slotWu(int state);
	void slotFire(int state);
	void slotBoom(int state);

	//�������ݲۺ���
	void slotAddNetArcgis();
	void slotRemvNetArcgis();

	//������Ƶ�ۺ���
	void slotPlayVideo();
signals:
	void startWork();
};

#endif // OSGCONTAINER_H