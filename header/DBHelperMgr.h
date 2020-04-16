
#ifndef DBHELPER_H
#define DBHELPER_H


#if defined(SLEHHDB_LIBRARY)
#  define SLEHHDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLEHHDBSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QThread>
#include "lwlglogout.h"
#include "sqlBackUp.h"
#include "sqlCreatConn.h"
#include "SqlInterface.h"

#include "baseDao.h"
//class SqlBackUp;
//class CreateConn;
//class SqlInterface;

class SLEHHDBSHARED_EXPORT CDBHelperMgr : public QObject
{
    Q_OBJECT
public:

    CDBHelperMgr(QObject *parent=0);

    ~CDBHelperMgr();

    ///备份
    bool  sqliteBackUp_WIN(QString path, QString dbName,QString backName);//备份
    bool  sqliteRecovery_WIN(QString path,QString recoveryName, QString dbName);//恢复

    ///初始化DB
    bool InitSqlite(QString dbPathName);

    /// SQL接口
//    BaseDao& getDao(){ return this->m_baseDao; }


    //查询
    QList<QVariantMap> queryList(QString sql,QVariantList params = QVariantList());

//    QSqlQueryModel *queryModel(QString sql);

    //执行sql语句
    bool exec(QString sql,QVariantList params = QVariantList(),int * lastInseredId = 0);

    //单个查询
    QVariant querySingleResult(QString sql,QVariantList params = QVariantList());

    //查询单个字段结果集
    QStringList queryOneFieldResult(QString sql,QVariantList params = QVariantList());

    //查询记录数
    int queryCount(QString sql,QVariantList params = QVariantList());


    bool beginTransaction();//开始事物
    bool endTransaction();//结束事物
    bool rollback();//回滚

signals:

public slots:

private:
    QScopedPointer<SqlBackUp>  m_sqlBackUp;
    QScopedPointer<CreateConn> m_CreateConn;
    QScopedPointer<SqlInterface> m_SqlInterface;

//    BaseDao m_baseDao;

};

#endif // DBHELPER_H
