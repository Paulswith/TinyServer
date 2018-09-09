#ifndef TSBODIESTABLEVIEW_H
#define TSBODIESTABLEVIEW_H

#include <QWidget>
#include <QTableView>

class TSBodiesTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TSBodiesTableView(QWidget *parent = nullptr);

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

    void reloadDataModel();
    void setBaseAttribute();
    void setMouseRightClickAttribute();

    void contextMenuEvent(QContextMenuEvent *event);

};

#endif // TSBODIESTABLEVIEW_H
