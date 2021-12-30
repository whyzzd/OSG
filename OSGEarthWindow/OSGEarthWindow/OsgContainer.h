#pragma once
#ifndef OSGCONTAINER_H
#define OSGCONTAINER_H

#include<qopenglwidget.h>
#include<osgViewer/Viewer>
#include<osgEarth/MapNode>
#include<osgEarthUtil/EarthManipulator>

extern osg::ref_ptr<osg::EllipsoidModel>em ;
extern osg::Node* createLine(osg::Vec3d start, osg::Vec3d end);

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
	void Pick(float x,float y);
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

	//¿ØÖÆÌØÐ§
	void createSnow();//Ñ©
	void createFire();//»ð
	void createExplosion();//±¬Õ¨
	void crateExplosionDebris();//±¬Õ¨ËéÆ¬

	//ÐÇ¿Õ
	void initSky();




protected:
	virtual void paintGL();

private:
	void init3D();
	void initCowTest();

	osg::ref_ptr<osg::Camera>createCamera(int x, int y, int w, int h);

private:
	osg::ref_ptr<osg::Group>root;
	osg::ref_ptr<osgViewer::GraphicsWindow >window;

	osg::Node* m_earthNode;
	
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;

public slots:
	void slotSnow(int state);
	void slotRain(int state);
	void slotWu(int state);
	void slotFire(int state);
	void slotBoom(int state);

};

#endif // OSGCONTAINER_H