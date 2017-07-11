#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T17:44:35
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_performancetesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($(GLDRS)/Glodon/shared/GLD.pri)
include($(GLDRS)/Glodon/shared/GSP.pri)

SOURCES += tst_performancetesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
