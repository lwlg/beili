#include "dlg_xs_add.h"
#include "ui_dlg_xs_add.h"

Dlg_XS_ADD::Dlg_XS_ADD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_XS_ADD)
{
    ui->setupUi(this);

    ui->txt_XS_SN->setText(XS_Tab::getjySn());
    ui->txt_XS_jytime->setText(XS_Tab::getjytime());

}

Dlg_XS_ADD::~Dlg_XS_ADD()
{
    delete ui;
}

XS_Tab Dlg_XS_ADD::getData()
{

    XS_Tab  mXStab;
    mXStab.jysn   = ui->txt_XS_SN->text();
    mXStab.jytime = ui->txt_XS_jytime->text();

    mXStab.brand = ui->txt_XS_brand->text();
    mXStab.jyCnt = ui->txt_XS_cnt->text().toInt();
    mXStab.price = ui->txt_XS_price->text().toInt()*100;
    mXStab.jine  = mXStab.getJine();

    mXStab.beizhu =ui->txt_XS_memo->text();
    mXStab.zftype =ui->comboBox->currentText();
    mXStab.unit =ui->txt_XS_unit->text();
    mXStab.zhonglei =ui->txt_XS_type->text();

    return mXStab;
}
