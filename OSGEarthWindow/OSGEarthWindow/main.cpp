#include "osgearthwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OSGEarthWindow w;
    w.show();
    return a.exec();
}
