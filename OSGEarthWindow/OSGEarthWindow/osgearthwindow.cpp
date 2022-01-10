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
	setWindowTitle("����");
	resize(600, 400);
	OsgContainer *osgViewer = new OsgContainer(/*argument,*/this);
	
	this->setCentralWidget(osgViewer);
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	
	//��Ч
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged,osgViewer,&OsgContainer::slotSnow);
	connect(ui.checkBoxRain, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotRain);
	connect(ui.checkBoxWu, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotWu);
	connect(ui.checkBoxFire, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotFire);
	connect(ui.checkBoxBoom, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotBoom);
	
	//������
	void(QComboBox::*activatedInt)(int) = &QComboBox::activated;//�������ذ汾
	connect(ui.comboBox, activatedInt, osgViewer->mCPickHandler, &CPickHandler::slotGetDrawIndex);
	connect(osgViewer->mCPickHandler, &CPickHandler::signReDefault, this, &OSGEarthWindow::slotReDefaultCombo);
	emit ui.comboBox->activated(0);//����Ĭ�Ͼ��л�Ծѡ��

	//ˮƽ����
	ui.horizontalSlider->setMinimum(10);
	ui.horizontalSlider->setMaximum(100);
	ui.horizontalSlider->setSingleStep(1);
	connect(this, &OSGEarthWindow::signDrawLineWid, osgViewer->mCPickHandler, &CPickHandler::slotDrawLineWid);
	connect(ui.horizontalSlider, &QSlider::valueChanged, [=](int value){
		float a = value / 10.0;
		emit signDrawLineWid(a);
	});
	emit signDrawLineWid(1.0);

	//����-�Ͽ�����
	connect(ui.pushButtonOpen, &QPushButton::clicked, osgViewer, &OsgContainer::slotAddNetArcgis);
	connect(ui.pushButtonClose, &QPushButton::clicked, osgViewer, &OsgContainer::slotRemvNetArcgis);

	//��ʾ��γ��
	mStatusLabel1 = new QLabel(this);
	mStatusLabel1->setMinimumWidth(100);
	ui.statusBar->addWidget(mStatusLabel1);
	ui.statusBar->setSizeGripEnabled(false);//ȥ��״̬�����½ǵ�����
	mStatusLabel1->setText(QString("��γ��:"));
	//��ʾ��Ϣ
	/*mStatusLabel2 = new  QLabel(this);*/
	connect(osgViewer->mCPickHandler, &CPickHandler::signShowLonLatAlt, this, &OSGEarthWindow::slotShowLonLatAlt);

}
void OSGEarthWindow::slotShowLonLatAlt(const osg::Vec3 &lla)
{
	mStatusLabel1->setText(QString("��γ��:(%1 , %2)").arg(lla.x()).arg(lla.y()));
}
void OSGEarthWindow::slotReDefaultCombo()
{
	ui.comboBox->setCurrentIndex(0);
	emit ui.comboBox->activated(0);
}