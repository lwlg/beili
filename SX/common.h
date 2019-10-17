#ifndef COMMON
#define COMMON

#define C_STR(qstr)                     qstr.toStdString().c_str()

#define DATETIME_STYLE  "yyyy-MM-dd hh:mm:ss"

#define DATETIME_STYLE_2  "yyyyMMddhhmmss"



#define QTableView_QSS_ALtColor     "QTableView::item:alternate:!selected, "\
                                    "QTableWidget::item:alternate:!selected, "\
                                    "QListView::item:alternate:!selected { background: #76B7BC; } "\
                                    "QTableView::item:!alternate:!selected, "\
                                    "QTableWidget::item:!alternate:!selected, "\
                                    "QListView::item:!alternate:!selected { background: #BCD7DA; }"


#endif // COMMON

