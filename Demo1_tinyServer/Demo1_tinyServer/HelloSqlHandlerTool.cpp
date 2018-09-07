#include "HelloSqlHandlerTool.h"

HelloSqlHandlerTool::HelloSqlHandlerTool(QString &sqlitePath, QString &sqlType)
{
    addDatabase(sqlType);
    setDatabaseName(sqlitePath);
    open();
}
