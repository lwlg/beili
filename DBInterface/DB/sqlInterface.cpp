#include "sqlInterface.h"
#include <QDebug>
#include <QTextCodec>

/***************************************************
 * 名称:sqlInterface
 * 功能:构造函数
 * 输入:parent对象
 * 输出:无
 * 备注:
 **************************************************/
SqlInterface::SqlInterface(QObject *parent) : QObject(parent)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    QTextCodec::setCodecForLocale(codec);
}

/***************************************************
 * 名称:query
 * 功能:查询sql
 * 输入:sql sql语句，params 查询参数
 * 输出:QList<QVariantMap> 结果集
 * 备注:
 **************************************************/
QList<QVariantMap> SqlInterface::queryList(QString sql, QVariantList params)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    QList<QVariantMap> result;
    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    QSqlQuery gquery(g_myDB);
    gquery.prepare(sql);
    for( int i = 0 ;i < params.size();i++)
    {
        QVariant & p = params[i];
        gquery.bindValue(i,p);
    }

    gquery.exec();
    while(gquery.next())
    {
        QSqlRecord record = gquery.record();
        int fieldCount = record.count();

        QVariantMap rowMap ;
        for(int i = 0 ; i < fieldCount ; i++)
        {
            QString fieldName = record.fieldName(i);
            QVariant fieldValue = record.value(i);
            qDebug() << fieldName << "----" << fieldValue.toString();
            rowMap.insert(fieldName,fieldValue);
        }
        result.append(rowMap);
    }
    QSqlError error = gquery.lastError();
    if(error.type() != QSqlError::NoError)
    {
        qDebug()<<error.text();
    }

    return result;
}

/***************************************************
 * 名称:queryModel
 * 功能:查询sql,返回一个QSqlQueryModel
 * 输入:sql sql语句
 * 输出:QSqlQueryModel 结果集
 * 备注:
 **************************************************/
QSqlQueryModel* SqlInterface::queryModel(QString sql)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    model->setQuery(sql,g_myDB);
//    QSqlRecord record = model->record();
//    int fieldCount = record.count();
//    for(int i = 0 ; i < fieldCount ; i++)
//    {
//        QString fieldName = record.fieldName(i);
//        model->setHeaderData(i,Qt::Horizontal,fieldName);
//    }
    return model;
}

/***************************************************
 * 名称:exec
 * 功能:sql执行函数
 * 输入:sql sql语句，params 查询参数，lastInseredId 插入id
 * 输出:false 失败，true 成功
 * 备注:
 **************************************************/
bool SqlInterface::exec(QString sql, QVariantList params, int *lastInseredId)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);
    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    QSqlQuery query(g_myDB);
    query.prepare(sql);
    for( int i = 0 ;i < params.size();i++)
    {
        QVariant & p = params[i];
        query.bindValue(i,p);
    }

    if(query.exec())
    {
        if(lastInseredId)
        {
            *lastInseredId = query.lastInsertId().toInt();
        }
        return true;
    }else
    {
        QSqlError error = query.lastError();
        qDebug()<<error.text();
        return false;
    }
}

bool SqlInterface::execSql(QString sql)
{
    QMutex              _mutex;
    QMutexLocker        lock(&_mutex);
    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    QSqlQuery query(g_myDB);

    if(query.exec(sql))
    {
        return true;
    }
    else
    {
        QSqlError error = query.lastError();
        qDebug()<<error.text();
        return false;
    }
}

QList<QVariantMap> SqlInterface::querySql(QString sql)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    QList<QVariantMap> result;
    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    QSqlQuery gquery(g_myDB);

    gquery.exec(sql);
    while(gquery.next())
    {
        QSqlRecord record = gquery.record();
        int fieldCount = record.count();

        QVariantMap rowMap ;
        for(int i = 0 ; i < fieldCount ; i++)
        {
            QString fieldName   = record.fieldName(i);
            QVariant fieldValue = record.value(i);
            qDebug() << fieldName << "----" << fieldValue.toString();
            rowMap.insert(fieldName,fieldValue);
        }
        result.append(rowMap);
    }
    QSqlError error = gquery.lastError();
    if(error.type() != QSqlError::NoError)
    {
        qDebug()<<error.text();
    }

    return result;
}

/***************************************************
 * 名称:querySingleResult
 * 功能:查询单个结果
 * 输入:sql sql语句，params 查询参数
 * 输出:QVariant 结果集
 * 备注:
 **************************************************/
QVariant SqlInterface::querySingleResult(QString sql, QVariantList params)
{
    QList<QVariantMap> result = queryList(sql,params);

    for(int i=0;i<result.size();i++)
    {
        QVariantMap map = result[i];
    }
    if(!result.isEmpty())
    {
        if(!result[0].isEmpty())
        {
            return result[0].first();
        }
    }
    return QVariant();
}

/***************************************************
 * 名称:queryOneFieldResult
 * 功能:查询单个字段结果集
 * 输入:sql sql语句，params 查询参数
 * 输出:QVariant 结果集
 * 备注:
 **************************************************/
QStringList SqlInterface::queryOneFieldResult(QString sql, QVariantList params)
{
    QList<QVariantMap> result = queryList(sql,params);

    QStringList list;
    for(int i=0;i<result.size();i++)
    {
        QVariantMap map = result[i];
        list << map.first().toString();
    }
    return list;
}

/***************************************************
 * 名称:queryCount
 * 功能:查询记录总数
 * 输入:sql sql语句，params 查询参数
 * 输出:记录数
 * 备注:
 **************************************************/
int SqlInterface::queryCount(QString sql, QVariantList params)
{
    QMutex              _mutex;
    _mutex.lock();
    int result=0;
    if(!g_myDB.isOpen())
    {
        g_myDB.open();
    }

    QSqlQuery query(g_myDB);
    query.prepare(sql);
    for( int i = 0 ;i < params.size();i++)
    {
        QVariant & p = params[i];
        query.bindValue(i,p);
    }

    query.exec();

    while(query.next())
    {
        result = query.value(0).toInt();
    }
    _mutex.unlock();
    return result;
}

/***************************************************
 * 名称:beginTransaction
 * 功能:开始事物
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
bool SqlInterface::beginTransaction()
{
    return g_myDB.transaction();
}

/***************************************************
 * 名称:endTransaction
 * 功能:结束事物
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
bool SqlInterface::endTransaction()
{
    return g_myDB.commit();
}

/***************************************************
 * 名称:rollback
 * 功能:回滚操作
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
bool SqlInterface::rollback()
{
    g_myDB.rollback();
}

