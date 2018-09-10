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
    inline QMap<QString, quint16> titleLabels(){
        QMap<QString, quint16> titleLabelInfos;
        titleLabelInfos["Path"] = 100;
        titleLabelInfos["Method"] = 100;
        titleLabelInfos["Requests"] = 250;
        titleLabelInfos["Response"] = 250;
        return titleLabelInfos;
    }

    void setBaseAttribute();
    void setMouseRightClickAttribute();
    void contextMenuEvent(QContextMenuEvent *event);

    //开启子窗口：
    void showAddBodyWindow();
    bool isAddBodyWindowOpened = false;

    void removeBodyItem();
};

#endif // TSBODIESTABLEVIEW_H
