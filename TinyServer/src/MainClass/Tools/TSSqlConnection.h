#ifndef TSSQLCONNECTION_H
#define TSSQLCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QScopedPointer>
#include <QStandardItem>
#include "MainClass/AppConfig/TSGlobalAttribute.h"

// 建表脚本： create table body_interaction(path TEXT not null, method TEXT,  reqjson JSON, rspJson JSON);
class TSSqlConnection
{
public:
    static QSqlDatabase getSqlConnection(bool *isOpen, QSqlError *error=nullptr);
    static void closeSqlConnection();

    // 查询全部的SQL, 暂未解耦, 所以这里还是返回QStandardItem了
    static QList<QList<QStandardItem *>> updateDataModel();
    // 查询该Path已经存在
    static bool isPathInDBsets(QString &path);
    // 插入数据
    static bool insertBodyData(const QStringList &insertList);
    // 更新数据
    static bool updateBodyDataWithPath(const QStringList &updateList);
    // 删除Path
    static void deleteExistPaths(const QString &path);
    // 从path拿全部数据
    static bodyStruct queryBodyItemWithPath(const QString path);
};

#endif // TSSQLCONNECTION_H
