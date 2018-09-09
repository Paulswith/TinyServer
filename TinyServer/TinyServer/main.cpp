#include <QApplication>
#include <QDebug>

#include "MainView/TSMainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSMainWindow w;
    w.show();

    return a.exec();
}

//Other/data.db
