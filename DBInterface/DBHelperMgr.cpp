#include "DBHelperMgr.h"

#include <QMetaType>
#include <QDebug>
#include <QTextCodec>

CDBHelperMgr::CDBHelperMgr(QObject *parent)
    : QObject(parent)
{
    this->m_sqlBackUp.reset(new SqlBackUp);
    this->m_CreateConn.reset(new CreateConn);
    this->m_SqlInterface.reset(new SqlInterface);
}

CDBHelperMgr::~CDBHelperMgr()
{

}

bool CDBHelperMgr::sqliteBackUp_WIN(QString path, QString dbName, QString backName)
{
    if(this->m_sqlBackUp.isNull())
        return false;

    return this->m_sqlBackUp.data()->sqliteBackUp_WIN(path,dbName,backName);
}

bool CDBHelperMgr::sqliteRecovery_WIN(QString path, QString recoveryName, QString dbName)
{
    if(this->m_sqlBackUp.isNull())
        return false;

    return this->m_sqlBackUp.data()->sqliteRecovery_WIN(path,recoveryName,dbName);
}

//  路径名称/../DB.db
bool CDBHelperMgr::InitSqlite(QString dbPathName)
{
    if(this->m_CreateConn.isNull())
        return false;

    this->m_CreateConn.data()->setDriver("QSQLITE");
    this->m_CreateConn.data()->setDBName(dbPathName);
    this->m_CreateConn.data()->openDB();
    return this->m_CreateConn.data()->isOpenDB();
}


QList<QVariantMap> CDBHelperMgr::queryList(QString sql, QVariantList params)
{
    QList<QVariantMap> _tmpMap;
    if(this->m_SqlInterface.isNull())
        return _tmpMap;
    return this->m_SqlInterface.data()->queryList(sql,params);
}

bool CDBHelperMgr::exec(QString sql, QVariantList params, int *lastInseredId)
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->exec(sql,params,lastInseredId);

}

QVariant CDBHelperMgr::querySingleResult(QString sql, QVariantList params)
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->querySingleResult(sql,params);
}

QStringList CDBHelperMgr::queryOneFieldResult(QString sql, QVariantList params)
{
    QStringList _tmpList;
    if(this->m_SqlInterface.isNull())
        return _tmpList;
    return this->m_SqlInterface.data()->queryOneFieldResult(sql,params);
}

int CDBHelperMgr::queryCount(QString sql, QVariantList params)
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->queryCount(sql,params);
}

bool CDBHelperMgr::beginTransaction()
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->beginTransaction();
}

bool CDBHelperMgr::endTransaction()
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->endTransaction();
}

bool CDBHelperMgr::rollback()
{
    if(this->m_SqlInterface.isNull())
        return false;
    return this->m_SqlInterface.data()->rollback();
}



