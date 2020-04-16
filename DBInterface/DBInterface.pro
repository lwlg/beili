#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T10:10:07
#
#-------------------------------------------------

QT       -= gui
QT       += core  sql


TARGET = SXAssiant
TEMPLATE = lib

CONFIG += plugin
CONFIG += c++11

DEFINES += SLEHHDB_LIBRARY


include($$PWD/DB/DBHelper.pri)

QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare -Wno-type-limits

DESTDIR+= $$PWD/../bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    $$PWD/../header/lwlglogout.h \
    $$PWD/../header/DBHelperMgr.h \
    $$PWD/../header/baseDao.h

SOURCES += \
    DBHelperMgr.cpp \
    baseDao.cpp
