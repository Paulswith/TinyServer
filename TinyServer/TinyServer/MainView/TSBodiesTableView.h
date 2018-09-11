#ifndef TSBODIESTABLEVIEW_H
#define TSBODIESTABLEVIEW_H

#include <QWidget>
#include <QTableView>

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
    void setMouseRightClickAttribute();
    void contextMenuEvent(QContextMenuEvent *event);

    //开启子窗口：
    void showAddBodyWindow();
    bool isAddBodyWindowOpened = false;

    // 删除item
    void removeBodyItem();

    //
//    void closeEvent(QCloseEvent *event);

};

#endif // TSBODIESTABLEVIEW_H
