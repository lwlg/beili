#ifndef DLG_MODIFY_JH_H
#define DLG_MODIFY_JH_H

#include <QDialog>
#include "datarecord.h"

namespace Ui {
class Dlg_Modify_JH;
}

class Dlg_Modify_JH : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Modify_JH(QWidget *parent = 0);
    ~Dlg_Modify_JH();

    JH_Tab getItemData();

    void setModItemData(JH_Tab& jh);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dlg_Modify_JH *ui;
};

#endif // DLG_MODIFY_JH_H
