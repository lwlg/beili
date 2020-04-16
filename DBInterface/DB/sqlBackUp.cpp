#include "sqlBackUp.h"
#include <QProcess>
//#include <stdlib.h>
#include "sqlDatabase.h"
#include <QDebug>

/***************************************************
 * 名称:SqlBackUp
 * 功能:构造函数
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
SqlBackUp::SqlBackUp(QObject *parent) : QObject(parent)
{

}

/***************************************************
 * 名称:sqliteBackUp
 * 功能:备份sqlite数据库
 * 输入:
 *     path：    数据库路径
 *     dbName：  备份前的名称
 *     backName：备份后的名称
 * 输出:true 成功，false 失败
 * 备注:
 **************************************************/
bool SqlBackUp::sqliteBackUp_WIN(QString path, QString dbName, QString backName)
{
    if(dbName.isEmpty() || backName.isEmpty() || path.isEmpty())//不能为空
    {
        return false;
    }

    //QString file = QString("copy %1 %2 \n").arg(path+"/"+dbName).arg(path+"/"+backName);
    QString file = QString("cd %1\n").arg(path);
//    qDebug() << file;
    QProcess *process = new QProcess();
    process->start("cmd");
    process->waitForStarted();
    int result = process->write(file.toLatin1().data());
    qDebug() << file << "--1--" << result;

//    file = QString("copy %1 %2 \n").arg(dbName).arg(backName);
//    process->write(file.toLatin1().data());
//    qDebug() << file << "--2--" << result;
//    process->closeWriteChannel();
//    process->waitForFinished();
//    process->close();
//    return true;

    process->closeWriteChannel();
    process->waitForFinished();
    process->close();

    QString filePath = path + "/" + backName;
    bool bret = false;
    if (QFile::exists(filePath)) {
        if(QFile::remove(filePath))
        {
            //直接复制
           bret = QFile::copy(dbName,filePath);
        }
        else{
            return false;
        }
    }
    else{
        //不存在直接复制
        bret = QFile::copy(dbName,filePath);
    }

    return bret;
}

/***************************************************
 * 名称:sqliteRecovery
 * 功能:恢复sqlite数据库
 * 输入:
 *     path：备份数据库所在路径
 *     dbName：恢复后的名称
 *     recoveryName：恢复前的名称
 * 输出:true 成功，false 失败
 * 备注:
 **************************************************/
bool SqlBackUp::sqliteRecovery_WIN(QString path,QString recoveryName, QString dbName)
{
    if(dbName.isEmpty() || path.isEmpty() || recoveryName.isEmpty())//不能为空
    {
        return false;
    }

    //QString file = QString("copy %1 %2 \n").arg(path+"/"+recoveryName).arg(path+"/"+dbName);
    QString file = QString("cd %1\n").arg(path);
    qDebug() << "sqliteRecovery-------" << file;
    QProcess *process = new QProcess();
    process->start("cmd");
    process->waitForStarted();
    int result = process->write(file.toLatin1().data());
    qDebug() << file << "--Recovery 1--" << result;
    file = QString("copy %1 %2 \n").arg(recoveryName).arg(dbName);
    result = process->write(file.toLatin1().data());
    qDebug() << file << "--Recovery 2--" << result;
    process->closeWriteChannel();
    process->waitForFinished();
    process->close();
    return true;
}

/***************************************************
 * 名称:mysqlBackUp
 * 功能:备份mysql数据库
 * 输入:
 *     toBackup：备份数据库的目的sql
 *     dbName：要备份的数据库名
 * 输出:true 成功，false 失败
 * 备注:
 **************************************************/
bool SqlBackUp::mysqlBackUp(QString toBackup,QString dbName)
{
    //不能为空
    if(dbName.isEmpty() || toBackup.isEmpty())
    {
        return false;
    }
    QString cmd = QString("mysqldump.exe -u %1 -p %2 %3 \n").arg(g_userName,g_password,dbName);
    QString Path = QString("%1").arg(toBackup);
    QProcess *poc=new QProcess;
    poc->setStandardOutputFile(Path);
    poc->start(cmd);
    return true;
}

/***************************************************
 * 名称:mysqlRecovery
 * 功能:恢复mysql数据库
 * 输入:
 *     fromBackup：恢复的备份数据库sql
 *     dbName：要恢复的数据库名
 * 输出:无
 * 备注:
 **************************************************/
bool SqlBackUp::mysqlRecovery(QString fromBackup,QString dbName)
{
    //不能为空
    if(dbName.isEmpty() || fromBackup.isEmpty())
    {
        return false;
    }
    QString cmd = QString("mysql.exe -u %1 -p %2 %3").arg(g_userName,g_password,dbName);
    QString Path = QString("%1").arg(fromBackup);
    QProcess *process=new QProcess;
    process->setStandardInputFile(Path);
    process->start(cmd);
    return true;
}

/***************************************************
 * 名称:odbcBackUp
 * 功能:构造函数
 * 输入:fileName
 * 输出:true 成功，false 失败
 * 备注:
 **************************************************/
bool SqlBackUp::odbcBackUp(QString fileName)
{

}

/***************************************************
 * 名称:createConn
 * 功能:odbcRecovery
 * 输入:fileName
 * 输出:true 成功，false 失败
 * 备注:
 **************************************************/
bool SqlBackUp::odbcRecovery(QString fileName)
{

}
