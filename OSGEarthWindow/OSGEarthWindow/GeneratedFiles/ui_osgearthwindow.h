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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSGEarthWindowClass
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuKais;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QCheckBox *checkBoxSnow;
    QCheckBox *checkBoxRain;
    QCheckBox *checkBoxWu;
    QCheckBox *checkBoxFire;
    QCheckBox *checkBoxBoom;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *OSGEarthWindowClass)
    {
        if (OSGEarthWindowClass->objectName().isEmpty())
            OSGEarthWindowClass->setObjectName(QStringLiteral("OSGEarthWindowClass"));
        OSGEarthWindowClass->resize(819, 524);
        actionExit = new QAction(OSGEarthWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(OSGEarthWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OSGEarthWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OSGEarthWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 819, 23));
        menuKais = new QMenu(menuBar);
        menuKais->setObjectName(QStringLiteral("menuKais"));
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


        gridLayout_2->addWidget(frame, 3, 0, 1, 1);

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

        comboBox = new QComboBox(dockWidgetContents);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        OSGEarthWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menuKais->menuAction());
        menuKais->addAction(actionExit);

        retranslateUi(OSGEarthWindowClass);

        QMetaObject::connectSlotsByName(OSGEarthWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *OSGEarthWindowClass)
    {
        OSGEarthWindowClass->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "OSGEarthWindow", Q_NULLPTR));
        actionExit->setText(QApplication::translate("OSGEarthWindowClass", "\351\200\200\345\207\272", Q_NULLPTR));
        menuKais->setTitle(QApplication::translate("OSGEarthWindowClass", "\345\274\200\345\247\213", Q_NULLPTR));
        dockWidget->setWindowTitle(QApplication::translate("OSGEarthWindowClass", "\345\212\237\350\203\275", Q_NULLPTR));
        pushButton->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("OSGEarthWindowClass", "PushButton", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("OSGEarthWindowClass", "\347\211\271\346\225\210", Q_NULLPTR));
        checkBoxSnow->setText(QApplication::translate("OSGEarthWindowClass", "\344\270\213\351\233\252", Q_NULLPTR));
        checkBoxRain->setText(QApplication::translate("OSGEarthWindowClass", "\344\270\213\351\233\250", Q_NULLPTR));
        checkBoxWu->setText(QApplication::translate("OSGEarthWindowClass", "\351\233\276", Q_NULLPTR));
        checkBoxFire->setText(QApplication::translate("OSGEarthWindowClass", "\347\201\253", Q_NULLPTR));
        checkBoxBoom->setText(QApplication::translate("OSGEarthWindowClass", "\347\202\270\345\274\271", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("OSGEarthWindowClass", "\346\227\240", Q_NULLPTR)
         << QApplication::translate("OSGEarthWindowClass", "\347\272\277", Q_NULLPTR)
         << QApplication::translate("OSGEarthWindowClass", "\351\235\242", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class OSGEarthWindowClass: public Ui_OSGEarthWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSGEARTHWINDOW_H
