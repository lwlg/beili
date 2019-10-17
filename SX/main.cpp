#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "inisettings.h"
#include "EasyLog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //1 加载日志
    LOGINIT();

    //2 加载配置文件
    theIni.settings_init(theIni.self_AppPath()+"\cfg.ini");
    LOGINFO("版本号:"+ theIni.getStrImp("config/version"));


    //3
    MainWindow w;
    w.show();

    return a.exec();
}
