//#include "Dao/baseDao.h"
#include "baseDao.h"

/***************************************************
 * 名称:BaseDao
 * 功能:构造函数
 * 输入:parent对象
 * 输出:无
 * 备注:
 **************************************************/
BaseDao::BaseDao(QObject *parent) : QObject(parent)
{

}
/***************************************************
 * 名称:~BaseDao
 * 功能:析构函数，释放资源
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
BaseDao::~BaseDao()
{

}

/***************************************************
 * 名称:add
 * 功能:添加一条记录
 * 输入:tableName 表名
 *     value 值列表(不可以为空)
 *     key  字段key列表(可以为空)
 * 输出:-1 参数无效，0 失败，1 成功
 * 备注:
 **************************************************/
int BaseDao::add(QString tableName, QVariantList value, QVariantList key)
{
    if(tableName.isEmpty()){//表名为空
            return -1;
    }

    if(value.size()<=0){//无插入值
        return -1;
    }

    QString sql = QString("insert into %1").arg(tableName);
    //拼接插入字段
    QString sql_key = "";
    if(0 < key.size())
    {
        sql_key.append("(");
        for(int i=0;i<key.size();i++)
        {
            if(0 != i){//非第一个条件，需要使用,隔开拼接
                sql_key.append(",");
            }
            sql_key.append(key[i].toString());
        }
        sql_key.append(")");
    }
    //拼接字段值
    QString sql_values = " values(";
    for(int i=0;i<key.size();i++)
    {
        if(0 != i){//非第一个条件，需要隔开
            sql_values.append(",");
        }
        sql_values.append("?");
    }
    sql_values.append(")");
    //真个sql语句的拼接
    sql.append(sql_key);
    sql.append(sql_values);
    qDebug() << "add:" << sql;
    //执行插入操作
    bool flag = m_Inter.exec(sql,value);
    if(flag)//插入成功
    {
        qDebug() << tr("add 插入成功。");
        return 1;
    }
    else{
        m_Inter.rollback();//回滚处理
        qDebug() << tr("add 插入失败。");
        return 0;
    }
}

/***************************************************
 * 名称:addMore
 * 功能:添加多条记录
 * 输入:tableName 表名
 *     values 值列表
 *     key  字段key列表
 * 输出:-1 参数无效，0 失败，1 成功
 * 备注:
 **************************************************/
int BaseDao::addMore(QString tableName, QList<QVariantList> values, QVariantList key)
{
    if(tableName.isEmpty())//表名为空
    {
        return -1;
    }

    if(values.size()<=0){//无插入值
        return -1;
    }

    QString sql = QString("insert into %1").arg(tableName);
    //拼接插入字段
    QString sql_key = "";
    if(0 < key.size())
    {
        sql_key.append("(");
        for(int i=0;i<key.size();i++)
        {
            if(0 != i){//非第一个条件需要使用,隔开
                sql_key.append(",");
            }
            sql_key.append(key[i].toString());
        }
        sql_key.append(")");
    }
    //拼接字段值
    QString sql_values = " values";
    QVariantList valuesAll;
    for(int i=0;i<values.size();i++)//多组值组合拼接
    {
        if(0 == i)//每组值括号拼接【(),()】
        {
            sql_values.append("(");
        }
        else{
            sql_values.append("),(");
        }

        for(int j=0;j<values[i].size();j++)//没一组值组合拼接
        {
            if(0 != j){//每组值的拼接【?,?】
                sql_values.append(",");
            }
            sql_values.append("?");
            valuesAll << values[i][j].toString();//值的拼接，全部转化为一个QVariantList
        }
    }
    sql_values.append(")");//最后一个括号

    //整个sql语句的拼接
    sql.append(sql_key);
    sql.append(sql_values);
//    qDebug() << "addMore:" << sql;
    //批量处理时，使用开启事物
    m_Inter.beginTransaction();
    //执行插入操作
    bool flag = m_Inter.exec(sql,valuesAll);
    //结束事物
    m_Inter.endTransaction();
    if(flag)//插入成功
    {
        qDebug() << tr("addMore 插入成功。");
        return 1;
    }
    else{
        m_Inter.rollback();//回滚处理
        qDebug() << tr("addMore 插入失败。");
        return 0;
    }
}

/***************************************************
 * 名称:deleteAll
 * 功能:删除所有信息
 * 输入:tableName 表名
 * 输出:-1 参数无效，0 失败，1 成功
 * 备注:
 **************************************************/
int BaseDao::deleteAll(QString tableName)
{
    if(tableName.isEmpty())//表名为空
    {
        return -1;
    }

    QString sql = QString("delete from %1").arg(tableName);
    //表中有多条记录时，使用事物快速处理
    m_Inter.beginTransaction();
    //执行删除操作
    bool flag = m_Inter.exec(sql);
    //结束事物
    m_Inter.endTransaction();
    if(flag)//插入成功
    {
        qDebug() << tr("删除成功。");
        return 1;
    }
    else{
        qDebug() << tr("删除失败。");
        return 0;
    }
}

/***************************************************
 * 名称:deleteByInfo
 * 功能:删除指定信息
 * 输入:tableName 表名
 *     value  条件值
 *     key    条件名称
 * 输出:-1 参数无效，0 失败，1 成功
 * 备注:
 **************************************************/
int BaseDao::deleteByInfo(QString tableName, QVariantList value, QVariantList key)
{
    if(tableName.isEmpty() || value.size()<=0 || key.size()<=0)//无效参数
    {
        return -1;
    }

    QString sql = QString("delete from %1 where ").arg(tableName);
    //where 条件组合
    QString tmp = "";
    for(int i=0;i<key.size();i++)
    {
        if(0 != i){//非第一个条件需要使用and连接
            tmp.append(" and ");
        }
        tmp.append(key[i].toString());
        tmp.append(" = ?");
    }
    sql.append(tmp);
    //执行删除操作
    bool flag = m_Inter.exec(sql,value);
    if(flag)//插入成功
    {
        qDebug() << tr("删除成功。");
        return 1;
    }
    else{
        qDebug() << tr("删除失败。");
        return 0;
    }
}
/***************************************************
 * 名称:selectToList
 * 功能:查询操作（返回一个list列表）
 * 输入:tableName 表名
 *     params 需要查询的字段
 *     value  条件值
 *     key    条件名称
 *     order  排序字段
 *     sort   排序 默认无排序,asc-升序，desc-降序
 * 输出:QList<QVariantMap>查询结果值
 * 备注:
 **************************************************/
QList<QVariantMap> BaseDao::selectToList(QString tableName, QVariantList params,QVariantList value,QVariantList key,QString sort,QString order)
{
    QList<QVariantMap> result;
    //表名不能为空
    if(tableName.isEmpty())
    {
        return result;
    }
    //判断字段个数和字段值个数是否相同
    if(value.size() != key.size()){
        return result;
    }

    //获取sql语句
    QString sql = setSQLFunc(tableName,1,params,key);

    //处理排序的条件
    QString tmp="";//默认是无排序条件
    if(sort == "desc" && !order.isEmpty())//降序
    {
        tmp.append(QString(" order by %1 desc").arg(order));
    }
    else if(sort == "asc" && !order.isEmpty())//升序
    {
        tmp.append(QString(" order by %1 asc").arg(order));
    }
    sql.append(tmp);

    qDebug() << "selectToList:" << sql;
    //批量处理时，使用开启事物
    m_Inter.beginTransaction();
    //执行插入操作
    result = m_Inter.queryList(sql,value);
    //结束事物
    m_Inter.endTransaction();

    return result;
}

//QList<QVariantMap> BaseDao::exeSql( QString sql)
//{
//    QList<QVariantMap> result;
//    //表名不能为空
//    if(sql == "")
//    {
//        return result;
//    }
//    qDebug() << "exeSql:" << sql;

//    //批量处理时，使用开启事物
//    m_Inter.beginTransaction();
//    //执行操作
//    result = m_Inter.querySql(sql);
//    //结束事物
//    m_Inter.endTransaction();

//    return result;
//}


/***************************************************
 * 名称:selectToModel
 * 功能:查询操作（返回一个model列表）
 * 输入:tableName 表名
 *     params 需要查询的字段
 *     value  条件值
 *     key    条件名称
 *     order  排序字段
 *     sort   排序 默认无排序,asc-升序，desc-降序
 * 输出:QSqlQueryModel查询结果值
 * 备注:
 **************************************************/
QSqlQueryModel *BaseDao::selectToModel(QString tableName, QVariantList params, QVariantList value, QVariantList key, QString sort, QString order)
{
    QSqlQueryModel* result;
    //表名不能为空
    if(tableName.isEmpty())
    {
        return result;
    }
    //判断字段个数和字段值个数是否相同
    if(value.size() != key.size()){
        return result;
    }

    //获取sql语句
    QString sql = setSQLFunc(tableName,0,params,key,value);

    //处理排序的条件
    QString tmp="";//默认是无排序条件
    if(sort == "desc" && !order.isEmpty())//降序
    {
        tmp.append(QString(" order by %1 desc").arg(order));
    }
    else if(sort == "asc" && !order.isEmpty())//升序
    {
        tmp.append(QString(" order by %1 asc").arg(order));
    }
    sql.append(tmp);

    qDebug() << "selectToModel:" << sql;
    //批量处理时，使用开启事物
    m_Inter.beginTransaction();
    //执行插入操作
    result = m_Inter.queryModel(sql);
    //结束事物
    m_Inter.endTransaction();

    return result;
}

/***************************************************
 * 名称:selectRecordCount
 * 功能:查询记录总数
 * 输入:tableName 表名(不允许为空)
 *     field 需要查询总数的字段(允许为空)
 *     value 值列表(允许为空)
 *     key   条件名称(允许为空)
 * 输出:-1 参数无效 其他查询记录总数
 * 备注:
 **************************************************/
int BaseDao::selectRecordCount(QString tableName, QString field,QVariantList key,QVariantList value)
{
    //表名不能为空
    if(tableName.isEmpty()){
        return -1;
    }
    //判断字段个数和字段值个数是否相同
    if(key.size()!=value.size()){
        return -1;
    }

    //组合查询字段
    QString sql = "select ";
    if(field.isEmpty())//表示查询所有字段再内的记录总数
    {
        sql.append(QString("count(*) from %1 ").arg(tableName));
    }
    else{//查询指定字段的记录总数
        sql.append(QString("count(%2) from %1 ").arg(tableName).arg(field));
    }

    //组合查询条件
    if(key.size()>0)//有查询条件
    {
        sql.append("where ");
        QString tmp = "";
        for(int i=0;i<key.size();i++)
        {
            if(0!=i){//非第一个条件
                tmp.append(" and ");
            }
            tmp.append(key[i].toString());
            tmp.append("=?");
        }
        sql.append(tmp);
    }
    qDebug() << "selectRecordCount:" << sql;
    return m_Inter.queryCount(sql,value);//返回记录数
}

/***************************************************
 * 名称:selectOneField
 * 功能:查询单个字段结果集列表
 * 输入:tableName 表名(不允许为空)
 *     params  查询字段名称
 *     value   查询条件值
 *     key     查询条件
 * 输出:查询结果集
 * 备注:
 **************************************************/
QStringList BaseDao::selectOneField(QString tableName, QString params, QVariantList value, QVariantList key)
{
    QStringList result;
    //表名和查询字段不能为空
    if(params.isEmpty() || tableName.isEmpty()){
        return result;
    }

    QString sql = QString("select %1 from %2").arg(params).arg(tableName);
    if(value.size() == key.size()){
        QString tmp="";
        if(key.size()>0)//有查询条件
        {
            sql.append(" where ");
            for(int i=0;i<key.size();i++)
            {
                if(0!=i){//非第一个条件
                    tmp.append(" and ");
                }
                tmp.append(key[i].toString());
                tmp.append("=?");
            }
            sql.append(tmp);
        }
    }
    result = m_Inter.queryOneFieldResult(sql,value);
    return result;
}
/***************************************************
 * 名称:selectPageList
 * 功能:分页查询
 * 输入:tableName 表名(不允许为空)
 *     curPage 当前分页
 *     pageSize   当前页记录总数
 *     params  查询参数
 *     whValue 查询条件值
 *     whKey   查询条件
 *     order  排序字段
 *     sort   排序 默认无排序,asc-升序，desc-降序
 * 输出:查询结果集(list类型)
 * 备注:
 **************************************************/
QList<QVariantMap> BaseDao::selectPageList(QString tableName, int curPage, int pageSize, QVariantList params, QVariantList whValue, QVariantList whKey, QString sort, QString order)
{
    QList<QVariantMap> result;
    QVariantList param;//条件值列表
    //表名不能为空,当前页；当前页，总记录数不能小于1
    if(tableName.isEmpty() || curPage<=0 || pageSize<=0)
    {
        return result;
    }
    //判断字段个数和字段值个数是否相同
    if(whValue.size() != whKey.size()){
        return result;
    }

    QString sql = "select ";
    if(params.size()>0){//查询字段设置
        for(int i=0;i<params.size();i++){
            if(0!=i){
                sql.append(",");
            }
            sql.append(params[i].toString());
        }
    }
    else{
        sql.append("*");//查询所有
    }
    sql.append(QString(" from %1 ").arg(tableName));
    if(whKey.size()>0){//有查询条件
        sql.append("where ");
        for(int i=0;i<whKey.size();i++){//where条件设置
            if(0!=i){
                sql.append(" and ");
            }
            sql.append(whKey[i].toString());
            sql.append("=?");
        }

        param << whValue;
    }

    //排序条件的设置
    QString tmp="";
    if(!order.isEmpty())
    {
        tmp.append(QString(" order by %1 ").arg(order));
    }
    //默认是无排序条件
    if(sort == "desc")//降序
    {
        tmp.append("desc ");
    }
    else if(sort == "asc")//升序
    {
        tmp.append("asc ");
    }
    sql.append(tmp);

    //分页条件设置
    //offset代表从第几条记录“之后“开始查询，limit表明查询多少条结果
    int offset = (curPage-1)*pageSize;
    if(("QSQLITE" == g_driver ) || ("QODBC" == g_driver))//sqlite和DM数据库
    {
        sql.append("limit ? offset ?");
        param << pageSize << offset;
    }
    else if("QMYSQL" == g_driver)//mysql数据库
    {
        //limit (2-1)*10,10
        sql.append("limit ?,?");
        param <<offset << pageSize;
    }

    //批量处理时，使用开启事物
    m_Inter.beginTransaction();
    //执行插入操作
    result = m_Inter.queryList(sql,param);
    //结束事物
    m_Inter.endTransaction();
    return result;
}

/***************************************************
 * 名称:selectPageModel
 * 功能:分页查询
 * 输入:tableName 表名(不允许为空)
 *     curPage 当前分页
 *     pageSize   当前页记录总数
 *     params  查询参数
 *     whValue 查询条件值
 *     whKey   查询条件
 *     order  排序字段
 *     sort   排序 默认无排序,asc-升序，desc-降序
 * 输出:查询结果集(model类型)
 * 备注:
 **************************************************/
QSqlQueryModel *BaseDao::selectPageModel(QString tableName, int curPage, int pageSize, QVariantList params, QVariantList whValue, QVariantList whKey, QString sort, QString order)
{
    QSqlQueryModel * result;
    //表名不能为空,当前页；当前页，总记录数不能小于1
    if(tableName.isEmpty() || curPage<=0 || pageSize<=0)
    {
        return result;
    }
    //判断字段个数和字段值个数是否相同
    if(whValue.size() != whKey.size()){
        return result;
    }

    QString sql = "select ";
    if(params.size()>0){//查询字段设置
        for(int i=0;i<params.size();i++){
            if(0!=i){
                sql.append(",");
            }
            sql.append(params[i].toString());
        }
    }
    else{
        sql.append("*");//查询所有
    }
    sql.append(QString(" from %1 ").arg(tableName));
    if(whKey.size()>0){//有查询条件
        sql.append("where ");
        for(int i=0;i<whKey.size();i++){//where条件设置
            if(0!=i){
                sql.append(" and ");
            }
            sql.append(whKey[i].toString());
            sql.append(QString("=%1").append(whValue[i].toString()));
        }
    }

    //排序条件的设置
    QString tmp="";
    if(!order.isEmpty())
    {
        tmp.append(QString(" order by %1 ").arg(order));
    }
    //默认是无排序条件
    if(sort == "desc")//降序
    {
        tmp.append("desc ");
    }
    else if(sort == "asc")//升序
    {
        tmp.append("asc ");
    }
    sql.append(tmp);

    //分页条件设置
    //offset代表从第几条记录“之后“开始查询，limit表明查询多少条结果
    int offset = (curPage-1)*pageSize;
    if(("QSQLITE" == g_driver ) || ("QODBC" == g_driver))//sqlite和DM数据库
    {
        sql.append(QString("limit %1 offset %2").arg(pageSize).arg(offset));
    }
    else if("QMYSQL" == g_driver)//mysql数据库
    {
        //limit (2-1)*10,10
        sql.append(QString("limit %1,%2").arg(offset).arg(pageSize));
    }

    //批量处理时，使用开启事物
    m_Inter.beginTransaction();
    //执行插入操作
    result = m_Inter.queryModel(sql);
    //结束事物
    m_Inter.endTransaction();
    return result;
}

/***************************************************
 * 名称:update
 * 功能:更新记录
 * 输入:tableName 表名（不允许为空）
 *     key   修改字段列表（不允许为空）
 *     value 修改值列表（不允许为空）
 *     whKey 条件字段列表（允许为空）
 *     whValue 条件值列表（允许为空）
 * 输出:-1 参数无效 其他查询记录总数
 * 备注:
 **************************************************/
int BaseDao::update(QString tableName, QVariantList key, QVariantList value, QVariantList whKey, QVariantList whValue)
{
    //表名不能为空
    if(tableName.isEmpty()){
        return -1;
    }
    //修改值无效,或者字段和值不对等
    if(key.size()<=0 || value.size()<=0
       || (key.size()!=value.size()) //修改值条件不对等
       || (whKey.size()!=whValue.size()))//条件值不对等
    {
        return -1;
    }

    QString sql = QString("update %1 set ").arg(tableName);
    //组合要更新的set语句
    QString tmp="";
    for(int i=0;i<key.size();i++){
        if(0!=i){//非第一个条件
            tmp.append(",");
        }
        tmp.append(key[i].toString());
        tmp.append("=?");
    }
    sql.append(tmp);//连接到sql语句上
    //组合要更新的条件
    tmp.clear();
    if(whKey.size()>0){
        tmp.append(" where ");
        for(int i=0;i<whKey.size();i++){
            if(0!=i){
                tmp.append(" and ");
            }
            tmp.append(whKey[i].toString());
            tmp.append("=?");
        }
        sql.append(tmp);//连接到sql语句上
        //把更新的值列表和条件值列表拼接到一起
        value << whValue;
    }

    qDebug() << "update:" << sql;
    //执行更新语句
    bool flag = m_Inter.exec(sql,value);
    if(flag)
    {
        qDebug() << tr("更新成功。");
        return 1;
    }
    else{
        m_Inter.rollback();//进行回滚操作
        qDebug() << tr("更新失败。");
        return 0;
    }
}

QList<QVariantMap> BaseDao::querySql(QString sql)
{
    return m_Inter.querySql(sql);
}

bool BaseDao::exeSql(QString sql)
{
    //开启事物
//    m_Inter.beginTransaction();
    //执行插入操作
    bool flag = m_Inter.execSql(sql);
    //结束事物
//    m_Inter.endTransaction();
    if(flag)//插入成功
    {
//        qDebug()<< tr("addMore 插入成功。");
        return true;
    }
    else{
//        m_Inter.rollback();//回滚处理
        qDebug() << tr("addMore 插入失败。");
        return false;
    }
}

//template<typename T>
//QList<T> BaseDao::selectToLists(T &a, QVariantList params, QVariantList value, QVariantList key, QString sort, QString order)
//{
//    QString tableName = QString(a);
//    selectToList(tableName,params,value,key,sort,order);
//}

/***************************************************
 * 名称:setSQLFunc
 * 功能:sql语句拼接的公共函数
 * 输入:tableName 表名
 *     flag   1标志返回list，0返回model
 *     params 需要查询的字段
 *     key    条件名称
 *     value  条件值
 * 输出:sql语句
 * 备注:
 **************************************************/
QString BaseDao::setSQLFunc(QString tableName,int flag, QVariantList params, QVariantList key, QVariantList value)
{
    QString sql = "";
    QString tmp = "";
    //查询字段拼接
    if(params.size()<=0){//查询所有字段
        sql.append(QString("select * from %1 ").arg(tableName));
    }
    else{//查询指定字段
        for(int i=0;i<params.size();i++)
        {
            if(0 != i){
                tmp.append(",");
            }
            tmp.append(params[i].toString());
        }
        sql.append(QString("select %1 from %2 ").arg(tmp).arg(tableName));
    }
    //查询条件拼接
    tmp.clear();
    if(key.size()>0)//有查询条件
    {
        sql.append("where ");
        for(int i=0;i<key.size();i++)
        {
            if(0!=i){//非第一个条件
                tmp.append(" and ");
            }
            tmp.append(key[i].toString());
            if(0 == flag){//返回model的查询条件
                tmp.append(QString("=%1").arg(value[i].toString()));
            }else{//返回list的查询条件
                tmp.append("=?");
            }
        }
        sql.append(tmp);
    }

    return sql;
}

