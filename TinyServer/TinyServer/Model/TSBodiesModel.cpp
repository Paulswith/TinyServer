#include <QStandardItem>
#include <QDebug>
#include <QSqlQuery>

#include "TSBodiesModel.h"
#include "Tools/TSSqlConnection.h"


TSBodiesModel::TSBodiesModel(QObject *parent)
    :QStandardItemModel (parent)
{
    // 可能存在数据更新, 一是添加的时候都通知刷新, 一个是进入的时候监听tab点击刷新 较好
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = TSSqlConnection::getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return;
    }

    QSqlQuery query(db);
    query.prepare("select * from requests");

    if (!query.exec()) {
        qDebug() << "query.lastError();" << query.lastError();
    }else{
        while(query.next()) {
            QList<QStandardItem *> items;
            QStandardItem *itemPath = new QStandardItem(query.value(0).toString());
            QStandardItem *method = new QStandardItem(query.value(1).toString());
            QStandardItem *reqParam = new QStandardItem(query.value(2).toString());
            // 把json('') 字符替换
            QStandardItem *reqJson = new QStandardItem( [&]() -> QString {
                                    QByteArray queryJson = query.value(3).toByteArray();
                                    return QString(queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, ""));
                                                        }());
            items <<itemPath << method << reqParam << reqJson;
            appendRow(items);
        }
    }




}
