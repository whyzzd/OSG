/********************************************************************************
** Form generated from reading UI file 'osgearthwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSGEARTHWINDOW_H
#define UI_OSGEARTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSGEarthWindowClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *OSGEarthWindowClass)
    {
        if (OSGEarthWindowClass->objectName().isEmpty())
            OSGEarthWindowClass->setObjectName(QStringLiteral("OSGEarthWindowClass"));
        OSGEarthWindowClass->resize(600, 400);
        centralWidget = new QWidget(OSGEarthWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OSGEarthWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OSGEarthWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        OSGEarthWindowClass->setMenuBar(menuBar);
        dockWidget = new QDockWidget(OSGEarthWindowClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setLayoutDirection(Qt::LeftToRight);
        dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame, 3, 1, 2, 2);

        widget = new QWidget(dockWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox_6 = new QCheckBox(widget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout_2->addWidget(checkBox_6, 5, 0, 1, 1);

        checkBox_3 = new QCheckBox(widget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_2->addWidget(checkBox_3, 2, 0, 1, 1);

        checkBox_2 = new QCheckBox(widget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 1, 0, 1, 1);

        checkBox_5 = new QCheckBox(widget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_2->addWidget(checkBox_5, 4, 0, 1, 1);

        checkBox_4 = new QCheckBox(widget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_2->addWidget(checkBox_4, 3, 0, 1, 1);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget, 1, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 2, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 3, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        OSGEarthWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(OSGEarthWindowClass);

        QMetaObject::connectSlotsByName(OSGEarthWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *OSGEarthWindowClass)
    {
        OSGEarthWindowClass->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "OSGEarthWindow", Q_NULLPTR));
        dockWidget->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "\345\212\237\350\203\275", Q_NULLPTR));
        pushButton->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox6", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox3", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox2", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox5", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox4", Q_NULLPTR));
        checkBox->setText(QApplication::translate("OSGEarthWindowClass", "CheckBox1", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSGEarthWindowClass: public Ui_OSGEarthWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSGEARTHWINDOW_H
