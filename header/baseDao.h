/***************************************************
 * 类名:baseDao.h
 * 功能:数据库服务接口
 **************************************************/

#ifndef BASEDAO_H
#define BASEDAO_H

#include <QObject>
#include <QtSql>
#include "sqlInterface.h"

#if defined(SLEHHDB_LIBRARY)
#  define SLEHHDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLEHHDBSHARED_EXPORT Q_DECL_IMPORT
#endif


class SLEHHDBSHARED_EXPORT BaseDao : public QObject
{
    Q_OBJECT
public:
    explicit BaseDao(QObject *parent = 0);

    ~BaseDao();

    /*增加*/
    //! 插入一条记录：value:插入一条记录值列表，key插入字段列表(可以为空)
    int add(QString tableName, QVariantList value, QVariantList key = QVariantList());

    //! 插入多条记录：values:插入值列表QVariantList为条记录，field插入字段列表
    int addMore(QString tableName,QList<QVariantList> values,QVariantList key = QVariantList());

    /*删除*/
    //! 删除所有
    int deleteAll(QString tableName);

    //! 根据一个或多个条件删除记录，value列表，key字段列表
    int deleteByInfo(QString tableName,QVariantList value = QVariantList(),QVariantList key = QVariantList());


    /*修改*/
    int update(QString tableName,QVariantList key, QVariantList value,QVariantList whKey = QVariantList(), QVariantList whValue=QVariantList());//修改所有记录

    /*执行查询sql*/
    QList<QVariantMap> querySql(QString sql);

    /*执行sql*/
    bool exeSql(QString sql);

    /*查询*/
    //! 查询所有记录，返回list
    QList<QVariantMap> selectToList(QString tableName, QVariantList params = QVariantList(), QVariantList value = QVariantList(), QVariantList key = QVariantList(),QString sort="",QString order="");

    //! 查询所有记录，返回model
    QSqlQueryModel * selectToModel(QString tableName, QVariantList params = QVariantList(), QVariantList value = QVariantList(), QVariantList key = QVariantList(),QString sort="",QString order="");

    //! 查询所有记录总数
    int selectRecordCount(QString tableName, QString field="", QVariantList key = QVariantList(), QVariantList value=QVariantList());

    //! 查询单个字段结果集列表
    QStringList selectOneField(QString tableName, QString params, QVariantList value = QVariantList(), QVariantList key = QVariantList());

    //分页查询
    //! 分页查询，返回list
    QList<QVariantMap> selectPageList(QString tableName, int curPage, int pageSize, QVariantList params = QVariantList(), QVariantList whValue = QVariantList(), QVariantList whKey = QVariantList(), QString sort="", QString order="");

    //! 分页查询，返回model
    QSqlQueryModel * selectPageModel(QString tableName, int curPage, int pageSize, QVariantList params = QVariantList(), QVariantList whValue = QVariantList(), QVariantList whKey = QVariantList(), QString sort="", QString order="");


    //测试
//    template<class T>
//    QList<T> selectToLists(T &a, QVariantList params = QVariantList(), QVariantList value = QVariantList(), QVariantList key = QVariantList(),QString sort="",QString order="");//查询所有记录，返回list

private:
    //sql语句拼接公共函数
    QString setSQLFunc(QString tableName, int flag, QVariantList params = QVariantList() = QVariantList(), QVariantList key = QVariantList(), QVariantList value = QVariantList());

private:
    SqlInterface m_Inter;
};

#endif // BASEDAO_H
