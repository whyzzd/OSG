#include "osgearthwindow.h"
#include"qtextedit.h"
#include"qdockwidget.h"
#include<qvboxlayout>
#include<QCheckBox>
#include<QListView>
#include<qpushbutton.h>
#include"OsgContainer.h"
OSGEarthWindow::OSGEarthWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("����");
	resize(800, 400);
	OsgContainer *osgViewer = new OsgContainer(this);
	this->setCentralWidget(osgViewer);
	
	//QTextEdit *mainText = new QTextEdit(this);
	//mainText->setText("main window");
	//mainText->setAlignment(Qt::AlignCenter);
	//this->setCentralWidget(mainText);//���˱༭�����ó������ڵ����봰��
	
	////����ͣ������
	//QDockWidget *dock = new QDockWidget("dockwidget1", this);
	//dock->setFeatures(QDockWidget::DockWidgetMovable);//���ô˴�����ƶ�
	//dock->setFeatures(QDockWidget::AllDockWidgetFeatures);//���ô˴�����������--�ɹر�,���ƶ�,�ɸ���
	//dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	//this->addDockWidget(Qt::RightDockWidgetArea, dock);

	//QWidget *rightWidget = new QWidget();
	//QVBoxLayout* vLayout = new QVBoxLayout();
	//vLayout->setSpacing(6);
	//vLayout->setContentsMargins(11, 11, 11, 11);
	//vLayout->setObjectName(QStringLiteral("verticalLayout"));
	//

	//QCheckBox* rainCheckBox = new QCheckBox();
	//rainCheckBox->setObjectName(QStringLiteral("rainCheckBox"));
	//rainCheckBox->setText(QStringLiteral("rain"));
	//vLayout->addWidget(rainCheckBox);

	//QCheckBox*snowCheckBox = new QCheckBox();
	//snowCheckBox->setObjectName(QStringLiteral("snowCheckBox"));
	//snowCheckBox->setText(QStringLiteral("snow"));
	//vLayout->addWidget(snowCheckBox);

	//QCheckBox*fogCheckBox = new QCheckBox();
	//fogCheckBox->setObjectName(QStringLiteral("fogCheckBox"));
	//fogCheckBox->setText(QStringLiteral("fog"));
	//vLayout->addWidget(fogCheckBox);

	//QCheckBox* smogCheckBox = new QCheckBox();
	//smogCheckBox->setObjectName(QStringLiteral("smogCheckBox"));
	//smogCheckBox->setText(QStringLiteral("smog"));
	//vLayout->addWidget(smogCheckBox);

	//QCheckBox* fireCheckBox = new QCheckBox();
	//fireCheckBox->setObjectName(QStringLiteral("fireCheckBox"));
	//fireCheckBox->setText(QStringLiteral("fire"));
	//vLayout->addWidget(fireCheckBox);

	//QCheckBox* bombCheckBox = new QCheckBox();
	//bombCheckBox->setObjectName(QStringLiteral("bombCheckBox"));
	//bombCheckBox->setText(QStringLiteral("bomb"));
	//vLayout->addWidget(bombCheckBox);

	//QPushButton *btn = new QPushButton();
	//
	//btn->resize(500, 500);
	//vLayout->addWidget(btn);
	////QListView* listView = new QListView();
	////listView->setObjectName(QStringLiteral("listView"));
	////listView->setGeometry(QRect(0, 0, 0, 0));
	////vLayout->addWidget(listView);
	//rightWidget->setLayout(vLayout);
	//
	//dock->setWidget(rightWidget);

}
