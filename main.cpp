#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //openni::OpenNI::initialize();
    QApplication a(argc, argv);
    MainWindow w;
    
    //openni::OpenNI::addDeviceConnectedListener(&w);
    //openni::OpenNI::addDeviceDisconnectedListener(&w);
    
    w.show();

    return a.exec();
}
