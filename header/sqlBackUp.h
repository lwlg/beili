/***************************************************
 * 类名:sqlBackUp.h
 * 功能:数据库备份与恢复接口类
 **************************************************/

#ifndef SQLBACKUP_H
#define SQLBACKUP_H

#include <QObject>

class SqlBackUp : public QObject
{
    Q_OBJECT
public:
    explicit SqlBackUp(QObject *parent = 0);
public://数据库备份与恢复接口
    //sqlite
    bool  sqliteBackUp_WIN(QString path, QString dbName,QString backName);//备份
    bool  sqliteRecovery_WIN(QString path,QString recoveryName, QString dbName);//恢复
    //mysql
    bool  mysqlBackUp(QString toBackup,QString dbName);//备份
    bool  mysqlRecovery(QString fromBackup,QString dbName);//恢复

    //odbc
    bool  odbcBackUp(QString fileName);//备份
    bool  odbcRecovery(QString fileName);//恢复
signals:

public slots:
};

#endif // SQLBACKUP_H
