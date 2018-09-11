#include <QStandardItem>
#include <QDebug>
#include <QSqlQuery>

#include "TSBodiesModel.h"
#include "Tools/TSSqlConnection.h"
#include "Model/TSGlobalAttribute.h"


TSBodiesModel::TSBodiesModel(QObject *parent)
    :QStandardItemModel (parent)
{
    // 可能存在数据更新, 一是添加的时候都通知刷新, 一个是进入的时候监听tab点击刷新 较好
    auto allBodyItems = TSSqlConnection::updateDataModel();
    foreach(QList<QStandardItem *> singleItem, allBodyItems){
        appendRow(singleItem);
    }
    // 更新全局paths
//    TSSqlConnection::updateExistPaths();
//    qDebug() << "alreadyExistPaths:" << GlobalStaticPro::alreadyExistPaths;
}
