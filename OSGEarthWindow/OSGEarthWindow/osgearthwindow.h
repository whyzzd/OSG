#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QMainWindow>
#include "ui_osgearthwindow.h"
#include <osgViewer/Viewer>
class OsgContainer;
class OSGEarthWindow : public QMainWindow
{
    Q_OBJECT

public:
	OSGEarthWindow(osg::ArgumentParser ap,QWidget *parent = Q_NULLPTR);

	//³õÊ¼»¯º¯Êý
	void initOSGViewer(osg::ArgumentParser ap);
	void initMenuBar();
	void initWeather();
	void initComboBox();
	void initSlider();
	void initButton();
	void initStatusBar();

	
private:
    Ui::OSGEarthWindowClass ui;

	QLabel *mStatusLabel1;
	QLabel *mStatusLabel2;
	OsgContainer *mOSGViewer;

signals:
	void signDrawLineWid(float a);
public slots:
	void slotShowLonLatAlt(const osg::Vec3 &lla);
	void slotReDefaultCombo();
};
