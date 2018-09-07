#ifndef HELLOSQLHANDLERTOOL_H
#define HELLOSQLHANDLERTOOL_H
#include <QtSql/QSqlDatabase>
#include <QObject>


class HelloSqlHandlerTool : public QObject
{
public:
    HelloSqlHandlerTool(QString & sqlitePath, QString & sqlType="QSQLITE");
};

#endif // HELLOSQLHANDLERTOOL_H
