#include "sqlhelper.h"
#include <QFile>
#include <QtSql>
#include <QTableWidget>
#include <QHeaderView>
#include "db_sql.h"
#include "SXGlobal.h"


SQLHelper::SQLHelper(QObject *parent) : QObject(parent)
{
    m_query = new QSqlQuery();
}

void SQLHelper::Init_SQL()
{
    // 打开ud数据库
    QString fileName = QCoreApplication::applicationDirPath() + DataPath_XSFile;
    bool udExist = QFile::exists(fileName);

    s_db_XS = QSqlDatabase::addDatabase("QSQLITE", "XSsqlite");
    s_db_XS.setDatabaseName(fileName);

    if(!s_db_XS.isOpen()){
        s_db_XS.open();
        lwlgout<<"XS_DB open success.";
    }

    if (!udExist)
    {
        QSqlQuery query(s_db_XS);
        query.exec(XS_CreateDB);
    }
}

///[1] 执行sql
bool SQLHelper::sql_Execute(QString sql)
{
    QSqlQuery query(s_db_XS);

    this->m_query =new QSqlQuery(query);

    this->m_query->prepare(sql);

    return this->m_query->exec();
}
///![1]


///[2] 获取实例
QSqlQuery *SQLHelper::getSqlQuery()
{
    return this->m_query;
}
///![2]


///
/// \brief SQLHelper::InitTableViewModel  销售表格表头设置
/// \param parent
/// \return
///
QSqlTableModel *SQLHelper::InitTableViewModel_XS(QObject *parent)
{
    QSqlTableModel *pModel = new QSqlTableModel(parent, s_db_XS);
    pModel->setTable("sx_xiaoshou");

    pModel->setHeaderData(0, Qt::Horizontal, "交易序号");
    pModel->setHeaderData(1, Qt::Horizontal, "交易时间");
    pModel->setHeaderData(2, Qt::Horizontal, "品牌");
    pModel->setHeaderData(3, Qt::Horizontal, "种类");
    pModel->setHeaderData(4, Qt::Horizontal, "单位");
    pModel->setHeaderData(5, Qt::Horizontal, "数量");
    pModel->setHeaderData(6, Qt::Horizontal, "单价");
    pModel->setHeaderData(7, Qt::Horizontal, "金额");
    pModel->setHeaderData(8, Qt::Horizontal, "支付方式");
    pModel->setHeaderData(9, Qt::Horizontal, "备注");

    pModel->sort(1, Qt::DescendingOrder); // 第0列排序

    return pModel;
}

//[]未使用
QSqlTableModel *SQLHelper::InitTableViewModel_JH(QObject *parent)
{
    QSqlTableModel *pModel = new QSqlTableModel(parent, s_db_XS);
    pModel->setTable("sx_jinhuo");//sqlite 里面表名称

    QStringList headerlst;
    headerlst<<"ID"<< "商品编码"<< "商品名称"<< "商品品牌"<< "商品型号"<< "商品单位"<< "进库数量"<< "单价"<< "金额"<< "供货厂家"<< "进货时间"<< "备注";

    for (int var = 0; var < headerlst.count(); var++)
    {
        pModel->setHeaderData(var, Qt::Horizontal, headerlst.at(var));
    }

    pModel->sort(0, Qt::DescendingOrder); // 第0列排序

    return pModel;
}

void SQLHelper::setTV_headerData(QSqlQueryModel* model, QStringList strlst)
{

    for (int ii = 0; ii < strlst.count(); ii++) {

        model->setHeaderData(ii,Qt::Horizontal, strlst.at(ii));
    }
}


