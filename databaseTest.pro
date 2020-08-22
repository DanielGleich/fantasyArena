QT += testlib sql
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

SOURCES += \
        database.cpp

HEADERS += \
        database.h \
        config.h

TEMPLATE = app

SOURCES +=  tst_databasetest.cpp
