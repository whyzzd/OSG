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
class CPickHandler;//无法直接包含,只能提前声明
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

	//控制特效
	bool createSnow();//雪
	bool createRain();
	void createWu();
	bool createFire();//火
	bool createBoom();//爆炸
	//bool crateExplosionDebris();//爆炸碎片

	//星空
	void initSky();

public:
	CPickHandler *mCPickHandler;


protected:
	virtual void paintGL();
	void initInteraction();

//声明initInteraction
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

	//网络传输操作包
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
	//以文件的形式加载
	void initEarth1();
	//以api的形式加载
	void initEarth2();
	void initCowTest();


private:
	osg::ref_ptr<osg::Camera>createCamera(int x, int y, int w, int h);
	osg::ref_ptr<osg::Group>root;
	osg::ref_ptr<osgViewer::GraphicsWindow >window;

	//用于存放地球节点和其它节点
	osgEarth::MapNode *m_mapNode;
	osg::Node* m_earthNode;
	
	osg::ref_ptr<osgEarth::Util::EarthManipulator> m_EM;
	osg::ref_ptr<osgEarth::Map>m_pMap;
	//网络图像层
	osg::ref_ptr<osgEarth::ImageLayer>m_netImageLayer;
	bool m_netIsOpen = false;
	QThread workerThread;
	Worker *mWorker=NULL;

	//测试用,无多线程
	osg::ref_ptr<osgEarth::ImageLayer>netImageLayer;

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

	//视频是否已存在
	bool mHaveVideo = false;

public slots:
	//特效槽函数
	void slotSnow(int state);
	void slotRain(int state);
	void slotWu(int state);
	void slotFire(int state);
	void slotBoom(int state);

	//网络数据槽函数
	void slotAddNetArcgis();
	void slotRemvNetArcgis();

	//播放视频槽函数
	void slotPlayVideo();

	/*void slotUndo();
	void slotRedo();*/
signals:
	void startWork();
};

#endif // OSGCONTAINER_H