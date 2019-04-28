#TEMPLATE = subdirs

QT       += core gui network sql
include(../Libs/QtWebApp/httpserver/httpserver.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyServer
TEMPLATE = app
#RC_FILE = exeIcon.rc

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
    MainClass/main.cpp \
    MainClass/Tools/TSSqlConnection.cpp \
    MainClass/Tools/TSHelpTools.cpp \
    MainClass/RespondEditor/View/TSBodyEditWidget.cpp \
    MainClass/Main/Controller/TSServerController.cpp \
    MainClass/Main/View/TSBodiesTableView.cpp \
    MainClass/Main/View/TSConsole.cpp \
    MainClass/Main/View/TSLCDClock.cpp \
    MainClass/Main/View/TSMainWindow.cpp \
    MainClass/Main/Model/TSBodiesModel.cpp \
    MainClass/Main/Model/TSGlobalAttribute.cpp \
    MainClass/Network/TSNetwork.cpp

HEADERS += \
    MainClass/Main/View/TSWindowDesign.hpp \
    MainClass/Tools/TSSqlConnection.h \
    MainClass/Tools/TSConfigUtil.h \
    MainClass/Tools/TSHelpTools.h \
    MainClass/RespondEditor/View/TSBodyEditWidget.h \
    MainClass/Main/Controller/TSServerController.h \
    MainClass/Main/View/TSBodiesTableView.h \
    MainClass/Main/View/TSConsole.h \
    MainClass/Main/View/TSLCDClock.h \
    MainClass/Main/View/TSMainWindow.h \
    MainClass/Main/Model/TSBodiesModel.h \
    MainClass/Main/Model/TSGlobalAttribute.h \
    MainClass/Network/TSNetwork.h

FORMS += \
    Resource/Form/TS_design.ui \
    Resource/Form/TSBodyEdit_design.ui

OTHER_FILES += Config/DB/data.db
OTHER_FILES += Config/Setting/config.ini

RESOURCES += \
    Resource/tsresource.qrc
