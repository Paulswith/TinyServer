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
    MainClass/MainWindow/Controller/TSServerController.cpp \
    MainClass/MainWindow/View/TSBodiesTableView.cpp \
    MainClass/MainWindow/View/TSConsole.cpp \
    MainClass/MainWindow/View/TSLCDClock.cpp \
    MainClass/MainWindow/View/TSMainWindow.cpp \
    MainClass/MainWindow/Model/TSBodiesModel.cpp \
    MainClass/AppConfig/TSGlobalAttribute.cpp \
    MainClass/Network/TSNetWork.cpp

HEADERS += \
    MainClass/MainWindow/View/TSWindowDesign.hpp \
    MainClass/Tools/TSSqlConnection.h \
    MainClass/Tools/TSConfigUtil.hpp \
    MainClass/Tools/TSHelpTools.h \
    MainClass/RespondEditor/View/TSBodyEditWidget.h \
    MainClass/MainWindow/Controller/TSServerController.h \
    MainClass/MainWindow/View/TSBodiesTableView.h \
    MainClass/MainWindow/View/TSConsole.h \
    MainClass/MainWindow/View/TSLCDClock.h \
    MainClass/MainWindow/View/TSMainWindow.h \
    MainClass/MainWindow/Model/TSBodiesModel.h \
    MainClass/AppConfig/TSGlobalAttribute.h \
    MainClass/Network/TSNetWork.h

FORMS += \
    Resource/Form/TS_design.ui \
    Resource/Form/TSBodyEdit_design.ui

OTHER_FILES += Config/DB/data.db
OTHER_FILES += Config/Setting/config.ini

RESOURCES += \
    Resource/tsresource.qrc
