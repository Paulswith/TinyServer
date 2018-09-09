#ifndef TSSQLCONNECTION_H
#define TSSQLCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QScopedPointer>
#include <QStandardItem>

/*
#define DECLARE_SINGLETON(Class) \
Q_DISABLE_COPY(Class) \
public: \
    static Class* Instance() \
    { \
        static QMutex mutex; \
        static QScopedPointer<Class> inst; \
        if (Q_UNLIKELY(!inst)) { \
            mutex.lock(); \
            if (!inst) inst.reset(new Class); \
            mutex.unlock(); \
        } \
        return inst.data(); \
    }
*/

class TSSqlConnection
{
public:
    static QSqlDatabase getSqlConnection(bool *isOpen, QSqlError *error=nullptr);
    static void closeSqlConnection();

    // 查询全部的SQL, 小项目倒是没有考虑解耦, 所以这里还是返回QStandardItem了
    static QList<QList<QStandardItem *>> getAllBodyItems();
    // 查询该Path已经存在
    static bool isPathInDBsets(QString &path);
    // 插入数据
    static bool insertBodyData(QStringList &insertList);
};

#endif // TSSQLCONNECTION_H
