#pragma once
#ifndef CPICKHANDLER_H
#define CPICKHANDLER_H
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector> // 新增头文件
#include<qdebug.h>
#include <osg/MatrixTransform>
#include"MyConvert.h"
#include<QObject>
#include<osgEarthAnnotation/FeatureEditing>
#include<QHash>
class OsgContainer;
class CPickHandler :public QObject, public osgGA::GUIEventHandler {
	Q_OBJECT
	
public:

	enum SelectedDraw {
		NONE=0,
		DOT=1,
		LINE = 2 ,
		TRIANGLES = 3,
		PARALLELOGRAM = 4,
		
	};
	int mSelected;

public:
	CPickHandler(osgViewer::Viewer *viewer); 
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	void pick(float x, float y);
	void pick1(float x, float y);
	osg::Vec3  pick2(float x, float y);
	void reDrawXXX();

	void drawDot(float x,float y);
	void drawLine();
	void drawTriangles();
	void drawParallelogram();

	void oldDrawLine();
	void oldDrawTriangles();
	void oldDrawParallelogram();

	OsgContainer *m_oc;

	bool mIsPickObject;
	osg::ref_ptr<osg::MatrixTransform> picked0;
	osg::ref_ptr < osgEarth::Annotation::FeatureEditor>picked;
	bool ispickededitor=false;
	osg::ref_ptr < osgEarth::Annotation::FeatureNode> pickednode;
	QHash<osgEarth::Annotation::FeatureEditor*, osgEarth::Annotation::FeatureNode*>m_kv;
	

	int mLineN = 1;
	float mLineXArr[5];
	float mLineYArr[5];
	//存放点击坐标以及点击次数
	osg::ref_ptr<osg::Vec3Array> mLineVec=new osg::Vec3Array;
	

	osg::ref_ptr<osg::Vec3Array> mTrinangleVec = new osg::Vec3Array;
	int mTrinangleN=1;
	
	osg::ref_ptr<osg::Vec3Array> mParallelogramVec = new osg::Vec3Array;
	int mParallelogramN=1;

	//滑动条的值
	float mDrawLineWid;

protected:
	osgViewer::Viewer *mViewer; // mViewer
	osg::Vec3 mWorld;
	
	MyConvert mMyConv;
public:
	osg::Vec3 mLonLatAlt;

	
signals:
	void signShowLonLatAlt(const osg::Vec3 &lla);
	void signReDefault();

public slots:
	void slotGetDrawIndex(int n);
	void slotDrawLineWid(float a);
	void slotActionUndo(bool checked=false);
	void slotActionRedo(bool checked = false);
	void slotActionDel(bool checked = false);
	void slotNetDel();
};
#endif