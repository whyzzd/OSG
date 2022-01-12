#pragma once


#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QMainWindow>
#include "ui_osgearthwindow.h"
#include <osgViewer/Viewer>

class OSGEarthWindow : public QMainWindow
{
    Q_OBJECT

public:
	OSGEarthWindow(QWidget *parent = Q_NULLPTR);

	QLabel *mStatusLabel1;
	QLabel *mStatusLabel2;
private:
    Ui::OSGEarthWindowClass ui;

signals:
	void signDrawLineWid(float a);
public slots:
	void slotShowLonLatAlt(const osg::Vec3 &lla);
	void slotReDefaultCombo();
};
