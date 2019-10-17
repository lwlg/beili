#include "dlg_modify_jh.h"
#include "ui_dlg_modify_jh.h"
#include <QDebug>

Dlg_Modify_JH::Dlg_Modify_JH(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Modify_JH)
{
    ui->setupUi(this);
}

Dlg_Modify_JH::~Dlg_Modify_JH()
{
    delete ui;
}

JH_Tab Dlg_Modify_JH::getItemData()
{
    JH_Tab r;

    r.GoodCode     = ui->dlgtxt_goodcode->text();
    r.GoodName     = ui->dlgtxt_goodname->text();
    r.GoodBrand    = ui->dlgtxt_goodbrand->text();
    r.GoodType     = ui->dlgtxt_goodtype->text();
    r.GoodUnit     = ui->dlgtxt_goodunit->text();
    r.GoodCnt      = ui->dlgtxt_goodcnt->text();
    r.Goodprice    = ui->dlgtxt_goodprice->text();
    r.Goodjine     = ui->dlgtxt_goodmoney->text();
    r.Goodsupplier = ui->dlgtxt_goodsupplier->text();
    r.Goodintime   = ui->dlgtxt_goodintime->text();
    r.GoodMemo     = ui->dlgtxt_goodmemo->text();
    return r;
}



void Dlg_Modify_JH::setModItemData(JH_Tab &jh)
{
    ui->dlgtxt_goodcode->setText(jh.GoodCode);
    ui->dlgtxt_goodname->setText(jh.GoodName);
    ui->dlgtxt_goodbrand->setText(jh.GoodBrand);
    ui->dlgtxt_goodtype->setText(jh.GoodType);
    ui->dlgtxt_goodunit->setText(jh.GoodUnit);
    ui->dlgtxt_goodcnt->setText(jh.GoodCnt);
    ui->dlgtxt_goodprice->setText(jh.Goodprice);
    ui->dlgtxt_goodmoney->setText(jh.Goodjine);
    ui->dlgtxt_goodsupplier->setText(jh.Goodsupplier);
    ui->dlgtxt_goodintime->setText(jh.Goodintime);
    ui->dlgtxt_goodmemo->setText(jh.GoodMemo);

}

void Dlg_Modify_JH::on_buttonBox_accepted()
{

    qDebug()<<"accept";
}

void Dlg_Modify_JH::on_buttonBox_rejected()
{
    qDebug()<<"reject";
}
