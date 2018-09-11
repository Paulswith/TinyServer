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

/**
~  1. 鼠标右键列表增删按钮, 删除Double-ensure
 ~ 2. 新增数据,在点击Commit的时候进行如下检查:
   ~  2.1 检查路径是否存在, 存在则不给新增
   ~  2.2 req-rsp, 都进行json语法检查,不通过不给新增

3. tableView追踪鼠标, 是否可以展示一个预览窗口


~  4. 请求进行判断, 路径符合,且参数符合就返回. POST-only
~  5. 对入库的JSON进行一下格式化为单行的。 // fromJson可以做到。

6. 直接新增编辑的功能. update来进行实现就可以了 update按钮的时候, 让path和commit - unable

// TO-DO:
数据库已经实现, 下一步把检查判断, 异常的不允许加入提示信息, 覆盖的实现SQL删除再插入.
入库的两个数据需要进行转JSON确认, ==POST才允许继续,目前支持.
*/
