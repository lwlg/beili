/***************************************************
 * 类名:createConn.h
 * 功能:创建数据库连接接口类
 **************************************************/


#ifndef CREATECONN_H
#define CREATECONN_H
#include <QObject>
#include <QtSql>
#include "sqlDatabase.h"

class CreateConn : public QObject
{
    Q_OBJECT
public:
    explicit CreateConn();
    ~CreateConn();

public://接口函数
    void setDriver(QString driverName);
    void setDBName(QString dbName);//设置数据库名称
    void setUserName(QString user);//设置用户名
    void setUserPass(QString pass);//设置密码
    void setUserHost(QString host);//设置主机
    void setUserPort(int port);//设置端口
    void openDB();//打开数据库
    bool isOpenDB();//判断数据库是否打开
    void closeDB();//关闭数据库

public:
};

#endif // CREATECONN_H
