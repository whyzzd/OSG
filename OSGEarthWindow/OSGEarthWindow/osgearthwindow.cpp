#pragma once
#include "osgearthwindow.h"
#include"qtextedit.h"
#include"qdockwidget.h"
#include<qvboxlayout>
#include<QCheckBox>
#include<QListView>
#include<qpushbutton.h>
#include"OsgContainer.h"
#include<QAction>
#include"CPickHandler.h"
#include<QLabel>
//#include"broadcaster.h"
//#include"receiver.h"
//#include"CameraPacket.h"
OSGEarthWindow::OSGEarthWindow(osg::ArgumentParser ap, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("地球");
	resize(800, 500);
	setMaximumSize(800, 500);
	setMinimumSize(800, 500);

	initOSGViewer(ap);
	initMenuBar();
	initWeather();
	initComboBox();
	initSlider();
	initButton();
	initStatusBar();
}
void OSGEarthWindow::initOSGViewer(osg::ArgumentParser ap)
{
	
	mOSGViewer = new OsgContainer(ap);
	mOSGViewer->setParent(this);
	this->setCentralWidget(mOSGViewer);


}

void OSGEarthWindow::initMenuBar()
{
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}
void OSGEarthWindow::initWeather()
{

	//特效
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged, mOSGViewer, &OsgContainer::slotSnow);
	connect(ui.checkBoxRain, &QCheckBox::stateChanged, mOSGViewer, &OsgContainer::slotRain);
	connect(ui.checkBoxWu, &QCheckBox::stateChanged, mOSGViewer, &OsgContainer::slotWu);
	connect(ui.checkBoxFire, &QCheckBox::stateChanged, mOSGViewer, &OsgContainer::slotFire);
	connect(ui.checkBoxBoom, &QCheckBox::stateChanged, mOSGViewer, &OsgContainer::slotBoom);
}
void OSGEarthWindow::initComboBox()
{
	//下拉框
	void(QComboBox::*activatedInt)(int) = &QComboBox::activated;//区分重载版本
	//connect(ui.comboBox, activatedInt, mOSGViewer->mCPickHandler, &CPickHandler::slotGetDrawIndex);
	connect(ui.comboBox, activatedInt, mOSGViewer, &OsgContainer::slotGetDrawIndex);
	connect(mOSGViewer->mCPickHandler, &CPickHandler::signReDefault, this, &OSGEarthWindow::slotReDefaultCombo);
	emit ui.comboBox->activated(0);//让其默认就有活跃选项
}
void OSGEarthWindow::initSlider()
{
	//水平滑轮
	ui.horizontalSlider->setMinimum(10);
	ui.horizontalSlider->setMaximum(100);
	ui.horizontalSlider->setSingleStep(1);
	connect(this, &OSGEarthWindow::signDrawLineWid, mOSGViewer->mCPickHandler, &CPickHandler::slotDrawLineWid);
	connect(ui.horizontalSlider, &QSlider::valueChanged, [=](int value) {
		float a = value / 10.0;
		emit signDrawLineWid(a);
	});
	emit signDrawLineWid(1.0);
}
void OSGEarthWindow::initButton()
{
	//---连接/断开网络
	connect(ui.pushButtonOpen, &QPushButton::clicked, mOSGViewer, &OsgContainer::slotAddNetArcgis);
	connect(ui.pushButtonClose, &QPushButton::clicked, mOSGViewer, &OsgContainer::slotRemvNetArcgis);

	//在球面播放视频
	connect(ui.pushButtonPlay, &QPushButton::clicked, mOSGViewer, &OsgContainer::slotPlayVideo);

}
void OSGEarthWindow::initStatusBar()
{
	//状态栏
	//显示经纬度
	mStatusLabel1 = new QLabel(this);
	mStatusLabel1->setMinimumWidth(100);
	ui.statusBar->addWidget(mStatusLabel1);
	ui.statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
	mStatusLabel1->setText(QString("经纬度:"));
	//提示信息
	/*mStatusLabel2 = new  QLabel(this);*/
	connect(mOSGViewer->mCPickHandler, &CPickHandler::signShowLonLatAlt, this, &OSGEarthWindow::slotShowLonLatAlt);
}
void OSGEarthWindow::slotShowLonLatAlt(const osg::Vec3 &lla)
{
	mStatusLabel1->setText(QString("经纬度:(%1 , %2)").arg(lla.x()).arg(lla.y()));
}
void OSGEarthWindow::slotReDefaultCombo()
{
	ui.comboBox->setCurrentIndex(0);
	emit ui.comboBox->activated(0);
}