/***************************************************
 * 类名:sqlDatabase.h
 * 功能:全局变量类
 **************************************************/

#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#pragma once
#include <QObject>
#include <QtSql>

extern QSqlDatabase  g_myDB;
extern QString g_driver;//驱动名称
extern QString g_userName;//数据库用户名
extern QString g_password;//数据库用户密码

#endif // SQLDATABASE_H
