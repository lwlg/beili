/*
    文件说明：qDebug()功能增强版，显示调试函数名称、行号、时间信息
    创建时间:2020-02-17
    修改时间:
    修改备注:
*/
#ifndef LWLGLOGOUT
#define LWLGLOGOUT
#include <QDebug>
#include <QDateTime>
#define LWLGD  //LWLG::日志开关,注释关闭打印日志
#ifdef LWLGD
//    #define lwlgout qDebug()<<"[lwlg]File"<<__FILE__<<",Line:"<<__LINE__<<">>"
      #define lwlgout qDebug().noquote()<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz [ddd]")\
       <<" [lwlg]File"<<__FILE__<<",Line:"<<__LINE__<<">>"
#else
    #define lwlgout qDebug()
#endif


#endif // LWLGLOGOUT

