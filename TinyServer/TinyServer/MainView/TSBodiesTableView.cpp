#include <QHeaderView>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QContextMenuEvent>
#include <QScrollBar>
#include <QSqlQuery>

#include "Tools/TSSqlConnection.h"
#include "TSBodiesTableView.h"
#include "Model/TSBodiesModel.h"


TSBodiesTableView::TSBodiesTableView(QWidget *parent)
    : QTableView(parent)
{
    reloadDataModel();
    setBaseAttribute();
}

void TSBodiesTableView::reloadDataModel()
{
    TSBodiesModel *model = new TSBodiesModel();
    setModel(model);                                 // 下方的列宽修改,需要基于已经设置好了model.

    // column-setting(当模型数据被修改了, title还是需要设置一遍):
    auto titleLabelInfos = titleLabels();
    model->setHorizontalHeaderLabels(titleLabelInfos.keys()); // set-titleLabel
    horizontalHeader()->setStretchLastSection(true); // 设置尾巴黏贴
    QMapIterator<QString, quint16> iter(titleLabelInfos);
    int iter_index = 0;
    while (iter.hasNext()) {
        iter.next();
        setColumnWidth(iter_index, iter.value());
        iter_index ++;
    }
}

void TSBodiesTableView::setBaseAttribute()
{
    // 不可编辑, 点击为行
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 隐藏水平滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void TSBodiesTableView::setMouseRightClickAttribute()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    auto menu = new QMenu();
    QAction *clickMeAction = menu->addAction("ClickMe");
    connect(this, &QWidget::customContextMenuRequested, [&](const QPoint &pos){
        int rowIndex = rowAt(pos.y());
        selectRow(rowIndex); // 选中改行
        menu->exec(QCursor::pos());
        qDebug() << "right-click: ";
    });

    connect(clickMeAction, &QAction::triggered, [&](){
        qDebug() << "clickMeAction->triggered";
    });
}

void TSBodiesTableView::contextMenuEvent(QContextMenuEvent *event)
{
    auto menu = new QMenu();
    QAction *clickMeAction = menu->addAction("ClickMe");
    connect(clickMeAction, &QAction::triggered, [&](){
        qDebug() << "clickMeAction->triggered";


    });
    menu->exec(QCursor::pos());
    qDebug() << "right-click: ";

    event->accept();
}


