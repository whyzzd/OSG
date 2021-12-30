#include "osgearthwindow.h"
#include"qtextedit.h"
#include"qdockwidget.h"
#include<qvboxlayout>
#include<QCheckBox>
#include<QListView>
#include<qpushbutton.h>
#include"OsgContainer.h"
OSGEarthWindow::OSGEarthWindow(/*osg::ArgumentParser argument,*/QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("µØÇò");
	resize(600, 400);
	OsgContainer *osgViewer = new OsgContainer(/*argument,*/this);
	
	this->setCentralWidget(osgViewer);
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged,osgViewer,&OsgContainer::slotSnow);
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotRain);
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotWu);
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotFire);
	connect(ui.checkBoxSnow, &QCheckBox::stateChanged, osgViewer, &OsgContainer::slotBoom);
		
}
