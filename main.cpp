#include "ui/mainwindow.h"
#include <QApplication>

#include <src/config/config.h>

Config*mainSystemConfig=NULL;

MainWindow*gobleMainWindow=NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainSystemConfig=new Config;

    mainSystemConfig->init();

    MainWindow w;

    gobleMainWindow=&w;

    w.show();

    return a.exec();
}
