#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "inisettings.h"
#include "datarecord.h"
#include "EasyLog.h"


class SQLHelper;
class QSqlTableModel;
class QTableView;
class QTableWidget;
class QSqlQueryModel;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    
    void setHeader_JHTB();

    void setHeader_XSTB();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Xiaoshou_sel_clicked();

    void on_btn_queryInGoods_clicked();

    void on_pushButton_JH_clean_clicked();

    void on_pushButton_JH_Add_clicked();

    void onDelete();

    void onModify();

    void on_pushButton_xsSave_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    void InitSQL();

    void InitUI();

    void InitTabView(QTableView *_tableView);

    void InitTableWidget(QTableWidget* _tabwid);

    void SetTabViewColumnSpace(QTableView *m_tableView);

    void paintEvent( QPaintEvent * e);

    bool eventFilter(QObject* obj, QEvent *evt);



private:
    Ui::MainWindow *ui;

    SQLHelper*  m_sql;

    QSqlQueryModel* pmode_jh;
    QSqlQueryModel* pmode_xs;

    QMenu   menu;

//    XS_Tab  mXStab;
    void InitDtCtlData();
};

#endif // MAINWINDOW_H
