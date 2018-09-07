#ifndef HELLOSQLCONNECTTOOL_H
#define HELLOSQLCONNECTTOOL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

class HelloSqlConnectTool : public QObject
{
public:
    explicit HelloSqlConnectTool(QObject *parent = nullptr);
    static QSqlDatabase initialDataBase(QString dbPath, QString driverType="QSQLITE");
};

#endif // HELLOSQLCONNECTTOOL_H
