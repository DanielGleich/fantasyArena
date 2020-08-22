QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_gametest.cpp \
        database.cpp \
        game.cpp \
        card.cpp

HEADERS += config.h \
        database.h \
        game.h \
        card.h

