#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SXGlobal.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTableView>
#include <QTableWidget>
#include <QPainter>
//
#include "sqlhelper.h"

#include "dlg_modify_jh.h"
#include "dlg_xs_add.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SNGener::readCnt();

    InitUI();

    InitSQL();

}

MainWindow::~MainWindow()
{
    SNGener::saveCnt();

    delete ui;
}

void MainWindow::InitSQL()
{
    InitSqlCon();//初始化打开db
}


void MainWindow::paintEvent(QPaintEvent *e)
{

}


///[右键菜单]
bool MainWindow::eventFilter(QObject *obj, QEvent *evt)
{
    if(obj == ui->tableViewJH  &&  evt->type() == QEvent::ContextMenu)
    {
        if(ui->tableViewJH->currentIndex().isValid()==true)
        {
            menu.exec(cursor().pos());//在当前鼠标位置上运行菜单menu对象
        }
    }
    return QMainWindow::eventFilter(obj,evt);
}
///![右键菜单]


///[进货表初始设置]
void MainWindow::setHeader_JHTB()
{
    QStringList headerlst;
    headerlst<<"ID"<< "商品编码"<< "商品名称"<< "商品品牌"<< "商品型号"<< "商品单位"<< "进库数量"<< "单价"<< "金额"<< "供货厂家"<< "进货时间"<< "备注";

    this->m_sql->setTV_headerData(this->pmode_jh,headerlst);

    ui->tableViewJH->setColumnWidth(0,100);

    ui->tableViewJH->setColumnHidden(0,true);
}

void MainWindow::setHeader_XSTB()
{
    QStringList headerlst;
    headerlst<<"交易序号"<< "交易时间"<< "品牌"<< "种类"<< "单位"<<"数量"<<"单价"<<"金额"<<"支付方式"<<"备注";

    this->m_sql->setTV_headerData(this->pmode_xs,headerlst);

    ui->tableViewSX->setColumnWidth(0,160);
    ui->tableViewSX->setColumnWidth(1,160);
    ui->tableViewSX->setColumnWidth(2,100);
    ui->tableViewSX->setColumnWidth(3,60);
    ui->tableViewSX->setColumnWidth(4,60);
    ui->tableViewSX->setColumnWidth(5,80);
    ui->tableViewSX->setColumnWidth(6,80);
    ui->tableViewSX->setColumnWidth(7,80);
}
///![进货表初始设置]


///[初始化UI]
void MainWindow::InitUI()
{
    this->setWindowTitle("贝助手 Ver:"+theIni.getStrImp("config/version"));

    this->InitTabView(ui->tableViewSX);

    this->InitTabView(ui->tableViewJH);

    this->pmode_jh = new QSqlQueryModel(this);//进货明细数据模型
    this->pmode_xs = new QSqlQueryModel(this);//销售数据模型


    //菜单设置
    ui->tableViewJH->installEventFilter(this);
    this->menu.addAction("修改",this,SLOT(onModify()));
    this->menu.addAction("删除",this,SLOT(onDelete()));


    InitDtCtlData();
}
///![初始化UI]
//////////////////////////////////////////////////////////////////////////////
void MainWindow::InitTabView(QTableView *_tableView)
{
    _tableView->horizontalHeader()->setFont(QFont("宋体",12));
    _tableView->setFont(QFont("微软雅黑",10));

    _tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    _tableView->setStyleSheet(QTableView_QSS_ALtColor);
    _tableView->setAlternatingRowColors(true);

    _tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::InitTableWidget(QTableWidget *_tabwid)
{
    _tabwid->horizontalHeader()->setFont(QFont("宋体",12));
    _tabwid->setFont(QFont("微软雅黑",10));

    _tabwid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _tabwid->setSelectionMode(QAbstractItemView::SingleSelection);
    _tabwid->setSelectionBehavior(QAbstractItemView::SelectRows);

    _tabwid->setStyleSheet(QTableView_QSS_ALtColor);
    _tabwid->setAlternatingRowColors(true);

    _tabwid->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::SetTabViewColumnSpace(QTableView *m_tableView)
{
    //根据内容来确定列宽度
        m_tableView->resizeColumnsToContents();
        m_tableView->horizontalHeader();
        //获取表头列数
        for(int i = 0; i < m_tableView->horizontalHeader()->count(); i++)
        {
            m_tableView->setColumnWidth(i, m_tableView->columnWidth(i) + 140);  //避免列内容挤
        }
        m_tableView->horizontalHeader()->setStretchLastSection(true);        //最后一列补全所有空白位置
}


//////////////////////////////////////////////////////////////////////////////



///[添加销售数据]
void MainWindow::on_pushButton_clicked()
{
    Dlg_XS_ADD dlg_xs_add;
    dlg_xs_add.exec();
    if (dlg_xs_add.result() == QDialog::Accepted)
    {
        //二次确认
        int r = QMessageBox::warning(this,"警告","是否添加此行数据?",QObject::tr("取消"),QObject::tr("确定"));
        if (r == QObject::tr("取消").toInt()) {
            lwlgout<<"cancle ;";
            return;
        }
       XS_Tab xsda = dlg_xs_add.getData();
       QString sql = xsda.toInsertSql();
       lwlgout<<sql;
       LOGINFO(sql);
       this->pmode_xs->setQuery(sql);
    }
}
///![]

///[查询所有]
void MainWindow::on_pushButton_xsSave_clicked()
{
    QString sql = QString::asprintf(XS_SelectAll);
    lwlgout<<sql;
    LOGINFO(sql);
    this->pmode_xs->setQuery(sql);
    ui->tableViewSX->setModel(this->pmode_xs);
    setHeader_XSTB();
}
///![]


///[销售表查询]
void MainWindow::on_pushButton_Xiaoshou_sel_clicked()
{
    QString strMemo = ui->txt_XS_memo->text();
    QString strbegin = ui->dt_XSbegin->text();
    QString strend = ui->dt_XSend->text();

    QString sql = QString::asprintf(XS_Select,C_STR(strMemo),
                                    C_STR(strbegin),
                                    C_STR(strend));
    lwlgout<<sql;
    LOGINFO(sql);
    this->pmode_xs->setQuery(sql);
    ui->tableViewSX->setModel(this->pmode_xs);
    setHeader_XSTB();
}
///![]

///[商品价格查询]
void MainWindow::on_btn_queryInGoods_clicked()
{
    QString gstrcode = ui->lineEdit_goodCode->text();
    QString gstrSupp = ui->lineEdit_goodsupplier->text();
    QString gstrGoodName   = ui->lineEdit_goodName->text();
    QString sql;

    if (ui->checkBox_GoodInTime->isChecked())
    {
        LOGINFO("加进货时间的查询");
//        QString gstrGoodInTime =  ui->dateEdit->text();
        QString gstrGoodInTime = ui->dateEdit->date().toString("yyyy-MM-dd");
        LOGINFO(gstrGoodInTime);

        sql = QString::asprintf(JH_PriceQuery_InTime, C_STR(gstrcode),C_STR(gstrSupp),C_STR(gstrGoodName),
                                        C_STR(gstrGoodInTime));
    }
    else
    {
        LOGINFO("不加进货时间的查询");
        sql = QString::asprintf(JH_PriceQuery, C_STR(gstrcode),C_STR(gstrSupp),C_STR(gstrGoodName));

    }

    lwlgout<<sql;
    LOGINFO(sql);
    this->pmode_jh->setQuery(sql);
    ui->tableViewJH->setModel(this->pmode_jh);
    setHeader_JHTB();


    int iret = this->pmode_jh->rowCount();
    if (iret != 0)
        QMessageBox::information(this,"查询提示",tr("查询成功,共%1条").arg(iret));
    else
        QMessageBox::warning(this,"查询提示",tr("未查询到数据").arg(iret));



}
///![商品价格查询]

///[入库信息清空]
void MainWindow::on_pushButton_JH_clean_clicked()
{
    ui->txt_goodCode->clear();
    ui->txt_goodName->clear();
    ui->txt_GoodBrand->clear();
    ui->txt_GoodType->clear();
    ui->txt_Gooduint->clear();
    ui->txt_goodcnt->clear();
    ui->txt_goodprice->clear();
    ui->txt_goodjine->clear();
    ui->txt_goodsupplier->clear();
    ui->txt_inGoodtime->clear();
    ui->txt_inGoodMemo->clear();

    ui->textBrowser->clear();
}
///![入库信息清空]

///[入库操作]
void MainWindow::on_pushButton_JH_Add_clicked()
{
    //二次确认
    int r = QMessageBox::warning(this,"警告","是否添加数据,请确定数据是否正确?",QObject::tr("取消"),QObject::tr("确定"));
    if (r == QObject::tr("取消").toInt()) {
        lwlgout<<"cancle add one row data;";
        return;
    }

    //检测输入范围
    if (ui->txt_goodName->text().isEmpty()||
            ui->txt_Gooduint->text().isEmpty()||
            ui->txt_goodcnt->text().isEmpty()||
            ui->txt_goodprice->text().isEmpty()||
            ui->txt_inGoodtime->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","输入为空\n请检查输入是否合法?",QObject::tr("确定"));
        LOGINFO("输入不合法,返回");
        return;
    }


    JH_Tab _tab;
    _tab.GoodCode = ui->txt_goodCode->text();
    _tab.GoodName = ui->txt_goodName->text();
    _tab.GoodBrand = ui->txt_GoodBrand->text();
    _tab.GoodType = ui->txt_GoodType->text();
    _tab.GoodUnit = ui->txt_Gooduint->text();

    _tab.GoodCnt = ui->txt_goodcnt->text();
    _tab.Goodprice = ui->txt_goodprice->text();
    _tab.Goodjine = ui->txt_goodjine->text();
    _tab.Goodsupplier = ui->txt_goodsupplier->text();
    _tab.Goodintime = ui->txt_inGoodtime->text();

    _tab.GoodMemo = ui->txt_inGoodMemo->text();

    QString sql = QString::asprintf(JH_Inser, C_STR(_tab.GoodCode),C_STR(_tab.GoodName),
                                    C_STR(_tab.GoodBrand),C_STR(_tab.GoodType),
                                    C_STR(_tab.GoodUnit),C_STR(_tab.GoodCnt),
                                    C_STR(_tab.Goodprice),C_STR(_tab.Goodjine),
                                    C_STR(_tab.Goodsupplier),C_STR(_tab.Goodintime),
                                    C_STR(_tab.GoodMemo));
    lwlgout<<sql;
    LOGINFO(sql);
    this->pmode_jh->setQuery(sql);

    QMessageBox::information(this,"提示","添加成功",QObject::tr("确定"));


    ui->textBrowser->append("添加成功.");

}
///![入库操作]

///[右键删除]
void MainWindow::onDelete()
{
    int row= ui->tableViewJH->currentIndex().row();
    QAbstractItemModel *model = ui->tableViewJH->model ();
    QModelIndex index = model->index(row,0);//选中行第一列的内容
    QVariant data = model->data(index);

    lwlgout<<data.toString();


    int r = QMessageBox::warning(this,"警告","是否删除改行?",QObject::tr("确定"),QObject::tr("取消"));
    if (r == QObject::tr("确定").toInt()) {
        QString sql = QString::asprintf(JH_Del, C_STR(data.toString()));
        lwlgout<<sql;
        this->pmode_jh->setQuery(sql);
        QMessageBox::information(this,"提示","删除数据成功!");
    }
}
///![右键删除]

///[修改操作]
void MainWindow::onModify()
{
    int columIndex = 0;//列索引
    int row= ui->tableViewJH->currentIndex().row();

    QAbstractItemModel *model = ui->tableViewJH->model();
    QString currentID = model->index(row,columIndex++).data().toString();

    JH_Tab objJH;
    objJH.GoodCode     = model->index(row,columIndex++).data().toString();
    objJH.GoodName     = model->index(row,columIndex++).data().toString();
    objJH.GoodBrand    = model->index(row,columIndex++).data().toString();
    objJH.GoodType     = model->index(row,columIndex++).data().toString();
    objJH.GoodUnit     = model->index(row,columIndex++).data().toString();
    objJH.GoodCnt      = model->index(row,columIndex++).data().toString();
    objJH.Goodprice    = model->index(row,columIndex++).data().toString();
    objJH.Goodjine     = model->index(row,columIndex++).data().toString();
    objJH.Goodsupplier = model->index(row,columIndex++).data().toString();
    objJH.Goodintime   = model->index(row,columIndex++).data().toString();
    objJH.GoodMemo     = model->index(row,columIndex++).data().toString();

    Dlg_Modify_JH dlg_modify;
    dlg_modify.setModItemData(objJH); //传值
    dlg_modify.exec();

    if (dlg_modify.result() == QDialog::Accepted)
    {
        //二次确认
        int r = QMessageBox::warning(this,"警告","是否修改此行数据?",QObject::tr("取消"),QObject::tr("确定"));
        if (r == QObject::tr("取消").toInt()) {
            lwlgout<<"cancle modify selected row data;";
            return;
        }


        lwlgout<<"修改确定";
        JH_Tab newJH = dlg_modify.getItemData();

        QString sql = QString::asprintf(JH_Update, C_STR(newJH.GoodCode),
                                        C_STR(newJH.GoodName),C_STR(newJH.GoodBrand),
                                        C_STR(newJH.GoodType),C_STR(newJH.GoodUnit),
                                        C_STR(newJH.GoodCnt),C_STR(newJH.Goodprice),
                                        C_STR(newJH.Goodjine),C_STR(newJH.Goodsupplier),
                                        C_STR(newJH.Goodintime),C_STR(newJH.GoodMemo),
                                        C_STR(currentID) );
        LOGINFO(sql);
        this->pmode_jh->setQuery(sql);
        QMessageBox::information(this,"提示","修改数据成功!");




    }
    else if(dlg_modify.result() == QDialog::Rejected)
    {

    }
}
///![修改操作]


void MainWindow::InitDtCtlData()
{
    QDateTime begin;
    begin.setDate(QDate::currentDate());
    begin.setTime(QTime(6,0,0));
    ui->dt_XSbegin->setDateTime(begin);
    ui->dt_XSend->setDateTime(QDateTime::currentDateTime());


    ui->dateEdit->setDate(QDate::currentDate());//库存表时间
}

///[切换界面]
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch (index) {
    case 1:
    {
        InitDtCtlData();
    }
        break;
    default:
        break;
    }
}
///![]

struct tongji_Select_Fields
{
    int   month;
    int   Money;
};

///[测试]
void MainWindow::on_pushButton_tc_sel_clicked()
{
    QString sTemp = QString(tongji);

    QList<tongji_Select_Fields> zdlist;

    QSqlQuery query;

    query.setForwardOnly(true);

    query.exec(sTemp);
    while (query.next())
    {
        tongji_Select_Fields bag;
        bag.month = query.value(0).toInt();
        bag.Money = query.value(1).toInt();

        zdlist.append(bag);
    }

    for (int var = 0; var < zdlist.count(); ++var) {

        QString _tmp = QString::asprintf("month=%d , Money=%d",zdlist.at(var).month,zdlist.at(var).Money);

        LOGINFO(">>" + _tmp);
    }

    ui->webView->setUrl(QUrl("file:///C:/Users/dell/Downloads/Compressed/QCharts-master/QCharts-master/QChart/qcharts.html"));

}
///![]
