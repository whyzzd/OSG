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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QCheckBox *checkBoxSnow;
    QCheckBox *checkBoxRain;
    QCheckBox *checkBoxWu;
    QCheckBox *checkBoxFire;
    QCheckBox *checkBoxBoom;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

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
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        checkBoxSnow = new QCheckBox(groupBox);
        checkBoxSnow->setObjectName(QStringLiteral("checkBoxSnow"));
        checkBoxSnow->setTristate(false);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, checkBoxSnow);

        checkBoxRain = new QCheckBox(groupBox);
        checkBoxRain->setObjectName(QStringLiteral("checkBoxRain"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, checkBoxRain);

        checkBoxWu = new QCheckBox(groupBox);
        checkBoxWu->setObjectName(QStringLiteral("checkBoxWu"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, checkBoxWu);

        checkBoxFire = new QCheckBox(groupBox);
        checkBoxFire->setObjectName(QStringLiteral("checkBoxFire"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, checkBoxFire);

        checkBoxBoom = new QCheckBox(groupBox);
        checkBoxBoom->setObjectName(QStringLiteral("checkBoxBoom"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, checkBoxBoom);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

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


        gridLayout_2->addWidget(frame, 2, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        OSGEarthWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(OSGEarthWindowClass);

        QMetaObject::connectSlotsByName(OSGEarthWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *OSGEarthWindowClass)
    {
        OSGEarthWindowClass->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "OSGEarthWindow", Q_NULLPTR));
        dockWidget->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "\345\212\237\350\203\275", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("OSGEarthWindowClass", "\347\211\271\346\225\210", Q_NULLPTR));
        checkBoxSnow->setText(QApplication::translate("OSGEarthWindowClass", "\344\270\213\351\233\252", Q_NULLPTR));
        checkBoxRain->setText(QApplication::translate("OSGEarthWindowClass", "\344\270\213\351\233\250", Q_NULLPTR));
        checkBoxWu->setText(QApplication::translate("OSGEarthWindowClass", "\351\233\276", Q_NULLPTR));
        checkBoxFire->setText(QApplication::translate("OSGEarthWindowClass", "\347\201\253", Q_NULLPTR));
        checkBoxBoom->setText(QApplication::translate("OSGEarthWindowClass", "\347\202\270\345\274\271", Q_NULLPTR));
        pushButton->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSGEarthWindowClass: public Ui_OSGEarthWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSGEARTHWINDOW_H
