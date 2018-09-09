#ifndef TSSQLCONNECTION_H
#define TSSQLCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QScopedPointer>

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

};

#endif // TSSQLCONNECTION_H
