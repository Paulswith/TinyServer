#include <QApplication>
#include <QDebug>

#include "MainClass/MainWindow/View/TSMainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSMainWindow w;
    w.show();

    return a.exec();
}

/**
待拓展需求,
1. 支持XML
2. 支持GET-post(已支持)
3. 支持通配* , 收到就回复请求
4. console美化下打印的格式
5. 取消IP展示
6. 修复消息体编辑的BUG和美化
7. 支持文件配置

更远的期望,可能开展的:
    全面支持正则字段标识

*/
