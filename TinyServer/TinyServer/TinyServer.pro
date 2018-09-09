#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T15:50:40
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    MainView/TSMainWindow.cpp \
    PushView/TSBodyEditWidget.cpp \
    MainView/TSConsole.cpp \
    MainView/TSBodiesTableView.cpp \
    Model/TSBodiesModel.cpp \
    Tools/TSSqlConnection.cpp

HEADERS += \
    MainView/TSMainWindow.h \
    PushView/TSBodyEditWidget.h \
    MainView/TSConsole.h\
    Design_Forms/TSWindowDesign.hpp \
    MainView/TSBodiesTableView.h \
    Model/TSBodiesModel.h \
    Tools/TSSqlConnection.h \
    Tools/TSConfigUtil.h

FORMS += \
    Design_Forms/TS_design.ui \
    Design_Forms/TSBodyEdit_design.ui

OTHER_FILES += Other/data.db
