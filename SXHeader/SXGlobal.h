#ifndef SXGLOBAL_H
#define SXGLOBAL_H

#include <QDebug>

#ifndef LWLGD
#define LWLGD  //LWLG::日志开关,注释关闭打印日志
    #ifdef LWLGD
        #define lwlgout qDebug()<<"[lwlg]File"<<__FILE__<<",Line:"<<__LINE__<<">>"
    #else
        #define lwlgout
    #endif
#endif


#endif//SXGLOBAL_H
