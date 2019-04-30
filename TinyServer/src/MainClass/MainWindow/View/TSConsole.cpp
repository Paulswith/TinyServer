#include <QScrollBar>
#include <QCoreApplication>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include "TSConsole.h"


TSConsole::TSConsole(QWidget *parent):
    QTextEdit(parent)
{
    setReadOnly(true);
    // 自动换行
    setLineWrapMode(QTextEdit::WidgetWidth);
}

/* ~~~~~~~~~~~~~~slots~~~~~~~~~~~~~~ */
void TSConsole::slotWithprint(QString content, PrintType colorType)
{
    prehandleColorContent(content, colorType);
    append(content);
    QScrollBar *scrollbar = verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
    // 自动刷新
    QCoreApplication::processEvents();
}

/* ~~~~~~~~~~~~~~private-methods~~~~~~~~~~~~~~ */
void TSConsole::prehandleColorContent(QString& content, PrintType colorType)
{
    QString color;
    switch (colorType) {
    case printStdsuc :
        color = "#50FA7B"; // 绿
        break;
    case printStderr:
        color = "#FF3C33"; // 红
        break;
    case printShine:
        color = "#8E44AD";
        break;
    default:
        color = "#17202A"; // 黑
        break;
    }
    content = "<span style=\" font-size:13pt; font-weight:600; color:" + color + ";\">" + content + "</span>";
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

