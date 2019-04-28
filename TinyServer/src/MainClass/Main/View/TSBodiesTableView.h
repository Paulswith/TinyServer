#ifndef TSBODIESTABLEVIEW_H
#define TSBODIESTABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include "MainClass/RespondEditor/View/TSBodyEditWidget.h"

class TSBodiesTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TSBodiesTableView(QWidget *parent = nullptr);
    void reloadDataModel();

private:
    // 初始化标题和标题宽度
    inline QPair<QStringList, QList<quint16>> titleLabels(){
        QStringList titleLabels = {"Path","Method", "Requests", "Response"};
        QList<quint16> columnWidth = {100, 100, 250, 250};
        return qMakePair(titleLabels, columnWidth);
    }

    void setBaseAttribute();
    void contextMenuEvent(QContextMenuEvent *event);

    //开启子窗口：
    TSBodyEditWidget *bodyEditWidget;
    void showAddBodyWindow();
    bool isAddBodyWindowOpened = false;

    // 获取当前行某列的text
    inline QString getCurrentRowText(const quint8 &column) {
        return currentIndex().sibling(currentIndex().row(),column).data().toString();}

    // 删除item
    void removeBodyItem();
    void viewBodyItem();
};

#endif // TSBODIESTABLEVIEW_H
