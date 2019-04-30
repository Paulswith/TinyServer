#ifndef TSHELPTOOLS_H
#define TSHELPTOOLS_H

#include <QString>
#include <QJsonDocument>
#include "MainClass/AppConfig/TSGlobalAttribute.h"

class TSHelpTools
{
public:
    TSHelpTools();
    // 验证是否为非法JSON
    static bool isInvalidJson(QString &checkContent, QString &analysJson);
    static bool isValidJson(QByteArray checkContent, QJsonDocument *analysJson);

    // 过滤json('')
    static QByteArray filterJsonPre(const QByteArray& jsonContent);

    // 查询 链接路径是否存在('')
    static bool isPathAlreadyExist(const QString &path);

    static bodyStruct queryBodyWithPath(const QString &path);

    /*上面不属于工具类的得干掉了~ 很多是数据库之类的*/
    static bool isPathExist(const QString& filePath);
};

#endif // TSHELPTOOLS_H
