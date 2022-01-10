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
OSGEarthWindow::OSGEarthWindow(/*osg::ArgumentParser argument,*/QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("地球");
	resize(600, 400);
	OsgContainer *osgViewer = new OsgContainer(/*argument,*/this);
	
	this->setCentralWidget(osgViewer);
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	
	//特效
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged,osgViewer,&OsgContainer::slotSnow);
	connect(ui.checkBoxRain, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotRain);
	connect(ui.checkBoxWu, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotWu);
	connect(ui.checkBoxFire, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotFire);
	connect(ui.checkBoxBoom, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotBoom);
	
	//下拉框
	void(QComboBox::*activatedInt)(int) = &QComboBox::activated;//区分重载版本
	connect(ui.comboBox, activatedInt, osgViewer->mCPickHandler, &CPickHandler::slotGetDrawIndex);
	connect(osgViewer->mCPickHandler, &CPickHandler::signReDefault, this, &OSGEarthWindow::slotReDefaultCombo);
	emit ui.comboBox->activated(0);//让其默认就有活跃选项

	//水平滑轮
	ui.horizontalSlider->setMinimum(10);
	ui.horizontalSlider->setMaximum(100);
	ui.horizontalSlider->setSingleStep(1);
	connect(this, &OSGEarthWindow::signDrawLineWid, osgViewer->mCPickHandler, &CPickHandler::slotDrawLineWid);
	connect(ui.horizontalSlider, &QSlider::valueChanged, [=](int value){
		float a = value / 10.0;
		emit signDrawLineWid(a);
	});
	emit signDrawLineWid(1.0);

	//连接-断开网络
	connect(ui.pushButtonOpen, &QPushButton::clicked, osgViewer, &OsgContainer::slotAddNetArcgis);
	connect(ui.pushButtonClose, &QPushButton::clicked, osgViewer, &OsgContainer::slotRemvNetArcgis);

	//显示经纬度
	mStatusLabel1 = new QLabel(this);
	mStatusLabel1->setMinimumWidth(100);
	ui.statusBar->addWidget(mStatusLabel1);
	ui.statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
	mStatusLabel1->setText(QString("经纬度:"));
	//提示信息
	/*mStatusLabel2 = new  QLabel(this);*/
	connect(osgViewer->mCPickHandler, &CPickHandler::signShowLonLatAlt, this, &OSGEarthWindow::slotShowLonLatAlt);

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