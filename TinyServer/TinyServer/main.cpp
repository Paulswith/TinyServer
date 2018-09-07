#include "TSMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSMainWindow w;
    w.show();

    return a.exec();
}
