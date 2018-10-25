#include "TSConsole.h"
#include <QScrollBar>
#include <QCoreApplication>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

TSConsole::TSConsole(QWidget *parent) : QTextEdit(parent)
{
    setReadOnly(true);
    // 设置自动换行
    setLineWrapMode(QTextEdit::WidgetWidth);
}

void TSConsole::showToConsole(QString content) {
    // 把内容添加
    append(prehandlerColorContent(content));
    // 获取滚动条
    QScrollBar *scrollbar = verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
    // 刷新, 整个比update管用
//    QWidget::repaint();
    QCoreApplication::processEvents();
}

QString TSConsole::prehandlerColorContent(QString content) {
    QString color;
    if (content.front() == '-') {
        color = colorUsing.kRed;
    } else if (content.front() == "#") {
        color = colorUsing.kOrange;
    } else{
        color = colorUsing.kGreen;
    }
    // 把第一个字符串替换替换掉 &
    content.replace(0, 1, "");
    return "<span style=\" font-size:13pt; font-weight:600; color:" +color+ ";\">"
           +content+ "</span>";
}

void TSConsole::contextMenuEvent(QContextMenuEvent *event) {
    // 鼠标右键: 清空日志
    auto menu = new QMenu();
    QAction *removeAction = menu->addAction("clear-log");
    connect(removeAction, &QAction::triggered, [&](){
        clear();
    });

    menu->exec(QCursor::pos());
    event->accept();
}
