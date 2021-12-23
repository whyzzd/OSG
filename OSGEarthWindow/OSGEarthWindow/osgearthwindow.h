#pragma once


#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QMainWindow>
#include "ui_osgearthwindow.h"

class OSGEarthWindow : public QMainWindow
{
    Q_OBJECT

public:
    OSGEarthWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::OSGEarthWindowClass ui;
};
