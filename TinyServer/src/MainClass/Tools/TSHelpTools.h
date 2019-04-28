#ifndef TSHELPTOOLS_H
#define TSHELPTOOLS_H

#include <QString>
#include <QJsonDocument>
#include "MainClass/Main/Model/TSGlobalAttribute.h"

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
};

#endif // TSHELPTOOLS_H
