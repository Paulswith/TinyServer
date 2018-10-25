#include <QHeaderView>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QContextMenuEvent>
#include <QScrollBar>
#include <QSqlQuery>
#include <QMessageBox>

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
    model->setHorizontalHeaderLabels(titleLabelInfos.first); // set-titleLabel
    horizontalHeader()->setStretchLastSection(true); // 设置尾巴黏贴
    for (int i=0;i < titleLabelInfos.second.count(); i++) {
        setColumnWidth(i, titleLabelInfos.second.at(i));
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
    // 鼠标右键列表增删按钮, 删除Double-ensure
    auto menu = new QMenu();
    QAction *ViewAction = menu->addAction("Edit-Item");
    if (isAddBodyWindowOpened) ViewAction->setEnabled(false);
    connect(ViewAction, &QAction::triggered, this, &TSBodiesTableView::viewBodyItem);

    QAction *addAction = menu->addAction("Add-Item");
    if (isAddBodyWindowOpened) addAction->setEnabled(false);
    connect(addAction, &QAction::triggered, this, &TSBodiesTableView::showAddBodyWindow);

    QAction *removeAction = menu->addAction("Remove-Item");
    if (model()->rowCount() == 0) removeAction->setEnabled(false);
    connect(removeAction, &QAction::triggered, this, &TSBodiesTableView::removeBodyItem);

    menu->exec(QCursor::pos());
    event->accept();
}

void TSBodiesTableView::viewBodyItem()
{
    QStringList currentItems;
    for(quint8 i=0; i<4;i++) {currentItems << getCurrentRowText(i);}
    // 先展示窗口再展示数据:
    showAddBodyWindow();
    if (isAddBodyWindowOpened && bodyEditWidget!=nullptr){
        bodyEditWidget->showViewWindowWithData(currentItems);
    }

//    bodyEditWidget->ts_path
}

void TSBodiesTableView::showAddBodyWindow()
{
    if (isAddBodyWindowOpened) return; // 避免重复打开
    QRect w_rect = geometry();
    // x+w+50

    QRect subRect(w_rect.x()+(w_rect.width()*2), w_rect.y() + 300, 400, 600);
    bodyEditWidget = new TSBodyEditWidget(subRect);
    bodyEditWidget->show();
    isAddBodyWindowOpened = true;
    connect(bodyEditWidget, &TSBodyEditWidget::signal_windowClose, [&](){
        // 子窗口关闭
        isAddBodyWindowOpened = false;
        bodyEditWidget = nullptr;  // 关闭的时候还是需要指向空
    });
    connect(bodyEditWidget, &TSBodyEditWidget::signal_addNewBody, [&](){
        reloadDataModel();
    });
}

void TSBodiesTableView::removeBodyItem()
{
    // 获取某列数据
    auto path = getCurrentRowText(0);

    switch(QMessageBox::warning(this, QString("Warning!"), QString("Sure delete this one?"),
                                QMessageBox::Yes, QMessageBox::Cancel))
    {
    case QMessageBox::Yes:
    qDebug() << "delete row: "<< path;
        TSSqlConnection::deleteExistPaths(path);
        reloadDataModel();
        break;

    case QMessageBox::Cancel:
        break;
    }
}

