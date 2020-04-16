/***************************************************
 * 类名:sqliteInterface.h
 * 功能:sqlite数据库操作接口类
 **************************************************/

#ifndef SQLDMLINTERFACE_H
#define SQLDMLINTERFACE_H

#include <QObject>
#include <QtSql>
#include "sqlDatabase.h"

#if defined(SLEHHDB_LIBRARY)
#  define SLEHHDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLEHHDBSHARED_EXPORT Q_DECL_IMPORT
#endif


class SLEHHDBSHARED_EXPORT SqlInterface : public QObject
{
    Q_OBJECT
public:
    explicit SqlInterface(QObject *parent = 0);

public://sql操作接口函数
    //查询
    QList<QVariantMap> queryList(QString sql,QVariantList params = QVariantList());

    QSqlQueryModel *queryModel(QString sql);

    //执行sql语句
    bool exec(QString sql,QVariantList params = QVariantList(),int * lastInseredId = 0);

    bool execSql(QString sql);

    //单个查询
    QList<QVariantMap> querySql(QString sql);

    QVariant querySingleResult(QString sql,QVariantList params = QVariantList());

    //查询单个字段结果集
    QStringList queryOneFieldResult(QString sql,QVariantList params = QVariantList());

    //查询记录数
    int queryCount(QString sql,QVariantList params = QVariantList());


    bool beginTransaction();//开始事物
    bool endTransaction();//结束事物
    bool rollback();//回滚
private:
};

#endif // SQLDMLINTERFACE_H
