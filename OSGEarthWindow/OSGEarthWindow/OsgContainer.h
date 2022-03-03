#pragma once
#pragma execution_character_set("UTF-8")
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

#include"broadcaster.h"
#include"receiver.h"
#include"CameraPacket.h"

#include<QMenu>
#include<QUndoCommand>
#include<QUndoStack>
class CPickHandler;//�޷�ֱ�Ӱ���,ֻ����ǰ����
class QInputEvent;
class OsgContainer :public QOpenGLWidget,public osgViewer::Viewer
{
	Q_OBJECT
public:
	OsgContainer(osg::ArgumentParser argument,QWidget *parent = 0);
	~OsgContainer();

	enum ViewerMode
	{
		STAND_ALONE,
		MASTER,
		SLAVE,
		SLAVE1
	};
	int mViewerMode;

	bool isPressed = false;
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

	void contextMenuEvent(QContextMenuEvent *event);
	QMenu *m_contextMenu;
	QAction *m_undoAction;
	QAction *m_redoAction;
	QAction *m_delAction;
	QUndoStack *m_undoStack;

	QUndoStack* getUndoStack()
	{
		return m_undoStack;
	}


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
	osgEarth::MapNode *getMapNode()
	{
		return m_mapNode;
	}

	//������Ч
	bool createSnow();//ѩ
	bool createRain();
	void createWu();
	bool createFire();//��
	bool createBoom();//��ը
	//bool crateExplosionDebris();//��ը��Ƭ

	//�ǿ�
	void initSky();

public:
	CPickHandler *mCPickHandler;


protected:
	virtual void paintGL();
	void initInteraction();

//����initInteraction
private:
	Broadcaster     mBC;
	Receiver        mRC;
	Broadcaster     mBC2;
	Receiver        mRC2;
	Receiver		mRC3;

	int mSocketNumber = 8100;


	CameraPacket *mCP;
	CameraPacket *mCP2;

	bool mMasterKilled = false;
	unsigned int mMessageSize = 1024;

	DataConverter *mScratchPad;
	DataConverter *mScratchPad2;

	//���紫�������
	struct OperaPacket
	{
		unsigned int _operaType;
		float _screenX;
		float _screenY;
		float _llaX;
		float _llaY;

		float _llaXArr[5];
		float _llaYArr[5];
		unsigned int _llaSize;
				
		OperaPacket():_operaType(0), _llaX(0.0f), _llaY(0.0f) {};
		OperaPacket(unsigned int operaType, float llaX, float llaY)
			:_operaType(operaType),
			_llaX(llaX),
			_llaY(llaY)
		{}
	};
public:
	OperaPacket mOperaPacket;

private:
	//���ļ�����ʽ����
	void initEarth1();
	//��api����ʽ����
	void initEarth2();
	void initCowTest();


private:
	osg::ref_ptr<osg::Camera>createCamera(int x, int y, int w, int h);
	osg::ref_ptr<osg::Group>root;
	osg::ref_ptr<osgViewer::GraphicsWindow >window;

	//���ڴ�ŵ���ڵ�������ڵ�
	osgEarth::MapNode *m_mapNode;
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

	/*void slotUndo();
	void slotRedo();*/
signals:
	void startWork();
};

#endif // OSGCONTAINER_H