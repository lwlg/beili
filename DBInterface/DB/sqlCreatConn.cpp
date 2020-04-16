#include "sqlCreatConn.h"
#include <QException>
#include <QDebug>
#include <QTextCodec>


//test
void createtable(){
    QSqlQuery     query(g_myDB);

    query.exec("create table DepartmentInfo (dep_id INTEGER PRIMARY KEY AUTOINCREMENT,dep_name varchar(20) not null)");//autoincrement自增，unique唯一索引
    query.exec("insert into DepartmentInfo values(1, 'aaa')");
    query.exec("insert into DepartmentInfo values(2, 'bbb')");
    query.exec("insert into DepartmentInfo values(3, 'ccc')");

    query.exec("create table GroupInfo (dep_id int,group_id INTEGER PRIMARY KEY AUTOINCREMENT,group_name varchar(20) not null)");
    query.exec("insert into GroupInfo values(1, 1, 'xxx')");
    query.exec("insert into GroupInfo values(2, 2, 'xdd')");
    query.exec("insert into GroupInfo values(3, 3, 'xcc')");
    query.exec("insert into GroupInfo values(1, 4, 'xaa')");

    query.exec("create table StaffInfo (group_id int,staff_id INTEGER PRIMARY KEY AUTOINCREMENT, staff_sex int(2) not null,staff_name varchar(20) not null)");
    query.exec("insert into StaffInfo values(1, 1,1,'saa')");
    query.exec("insert into StaffInfo values(2, 2,0,'sbb')");
    query.exec("insert into StaffInfo values(3, 3,0,'scc')");
    query.exec("insert into StaffInfo values(2, 4,1,'sdd')");
}

/***************************************************
 * 名称:createConn
 * 功能:构造函数
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
CreateConn::CreateConn()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    QTextCodec::setCodecForLocale(codec);
}

/***************************************************
 * 名称:setDriver
 * 功能:设置数据库驱动名称
 * 输入:driverName：数据库驱动名称
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setDriver(QString driverName)
{
    try{
        //驱动名称为不能为空
        if(driverName.isEmpty())
        {
            //抛出数据库名称不能为空的异常信息
        }
        g_driver = driverName;
        //获取所有数据库驱动进行校验
        QStringList driverList = QSqlDatabase::drivers();
        qDebug() << driverList;
        if(driverList.contains(g_driver))
        {
            //抛出数据库驱动不对的异常信息
        }
        g_myDB = QSqlDatabase::addDatabase(g_driver,"hf_all");//第二个参数标志唯一，以防冲突
    }
    catch(QException){
        qDebug()<<"throw exception";
    }
}

/***************************************************
 * 名称:CreateConn
 * 功能:析构函数 释放资源
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
CreateConn::~CreateConn(){
    //关闭数据库
    closeDB();
}

/***************************************************
 * 名称:setDBName
 * 功能:设置数据库名称
 * 输入:dbName 名称
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setDBName(QString dbName)
{
    if(!dbName.isEmpty())
    {
        g_myDB.setDatabaseName(dbName);
    }
}

/***************************************************
 * 名称:setUserName
 * 功能:设置用户名称
 * 输入:user 用户名称
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setUserName(QString user)
{
    if(!user.isEmpty())
    {
        g_userName=user;
        g_myDB.setUserName(user);
    }
}

/***************************************************
 * 名称:setUserPass
 * 功能:设置用户密码
 * 输入:pass 用户密码
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setUserPass(QString pass)
{
    if(!pass.isEmpty())
    {
        g_password=pass;
        g_myDB.setPassword(pass);
    }
}

/***************************************************
 * 名称:setUserHost
 * 功能:设置地址
 * 输入:host 地址
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setUserHost(QString host)
{
    if(!host.isEmpty())
    {
        g_myDB.setHostName(host);
    }
}

/***************************************************
 * 名称:setUserPort
 * 功能:设置端口
 * 输入:port 端口
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::setUserPort(int port)
{
    if(port>0)
    {
        g_myDB.setPort(port);
    }
}

/***************************************************
 * 名称:openDB
 * 功能:打开数据库
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::openDB()
{
    //校验数据库是否已经打开
    if (!g_myDB.open()) {
        qDebug() << g_myDB.lastError().text();
        QString msg = QString("Cannot open database.\n Unable to establish a database connection.\n"
                "This example needs %1 support. Please read "
                "the Qt SQL driver documentation for information how "
                "to build it.\n\n"
                "Click Cancel to exit.").arg(g_driver);
        qDebug() << msg;
        qDebug() << tr("数据库连接失败。");
    }
    else{
        qDebug() << tr("数据库连接成功。");
    }
//    createtable();
}

/***************************************************
 * 名称:isOpenDB
 * 功能:校验数据库是否打开
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
bool CreateConn::isOpenDB()
{
    bool flag = g_myDB.isOpen();
    return flag;
}

/***************************************************
 * 名称:closeDB
 * 功能:关闭数据库
 * 输入:无
 * 输出:无
 * 备注:
 **************************************************/
void CreateConn::closeDB()
{
    g_myDB.close();
}
