#-------------------------------------------------
#
# Project created by QtCreator 2019-07-03T22:51:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SX
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlhelper.cpp \
    dlg_modify_jh.cpp \
    inisettings.cpp \
    EasyLog.cpp \
    sngener.cpp \
    dlg_xs_add.cpp

HEADERS  += mainwindow.h \
    sqlhelper.h \
    db_sql.h \
    datarecord.h \
    common.h \
    dlg_modify_jh.h \
    inisettings.h \
    EasyLog.h \
    sngener.h \
    dlg_xs_add.h

FORMS    += mainwindow.ui \
    dlg_modify_jh.ui \
    dlg_xs_add.ui

DESTDIR += $$PWD/../bin

INCLUDEPATH +=$$PWD/../SXHeader
#LIBS    += -L$$PWD/../bin

#加入图标和版本号
RC_FILE     += version.rc
