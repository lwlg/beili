#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QObject>
#include <QMutex>
#include <QSqlTableModel>
#include <QSqlQuery>

#include <QTableView>


static QSqlDatabase s_db_XS;         // 销售数据库


static bool InitSqlCon()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sx.db");
    if(!db.open())
        return false;
    return true;
}

class SQLHelper : public QObject
{
    Q_OBJECT
public:
    explicit SQLHelper(QObject *parent = 0);

//    void Init_SQL();
    static void Init_SQL();

    bool sql_Execute(QString sql);

    QSqlQuery* getSqlQuery();

    QSqlTableModel*  InitTableViewModel_XS(QObject *parent=0);

    QSqlTableModel*  InitTableViewModel_JH(QObject *parent=0);

    void setTV_headerData(QSqlQueryModel *model, QStringList strlst);
signals:

public slots:

private:
   QMutex          m_udMutex;

   QSqlQuery*       m_query;
};

#endif // SQLHELPER_H
