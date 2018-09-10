#ifndef TSSQLCONNECTION_H
#define TSSQLCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QScopedPointer>
#include <QStandardItem>

// 建表脚本： create table body_interaction(path TEXT not null, method TEXT,  reqjson JSON, rspJson JSON);
class TSSqlConnection
{
public:
    static QSqlDatabase getSqlConnection(bool *isOpen, QSqlError *error=nullptr);
    static void closeSqlConnection();

    // 查询全部的SQL, 暂未解耦, 所以这里还是返回QStandardItem了
    static QList<QList<QStandardItem *>> getAllBodyItems();
    // 查询该Path已经存在
    static bool isPathInDBsets(QString &path);
    // 插入数据
    static bool insertBodyData(QStringList &insertList);
    // 缓存已存在Path
    static void updateExistPaths();
    // 删除Path
    static void deleteExistPaths(QString &path);
    // DELETE FROM body_interaction WHERE path='/path1';
};

#endif // TSSQLCONNECTION_H
