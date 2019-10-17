#ifndef DLG_XS_ADD_H
#define DLG_XS_ADD_H

#include <QDialog>
#include "common.h"
#include "datarecord.h"

namespace Ui {
class Dlg_XS_ADD;
}

class Dlg_XS_ADD : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_XS_ADD(QWidget *parent = 0);
    ~Dlg_XS_ADD();


    XS_Tab getData();
private:
    Ui::Dlg_XS_ADD *ui;
};

#endif // DLG_XS_ADD_H
