#ifndef TSHELPTOOLS_H
#define TSHELPTOOLS_H

#include <QString>
#include <QJsonDocument>
#include "Model/TSGlobalAttribute.h"

class TSHelpTools
{
public:
    TSHelpTools();
    // 验证是否为非法JSON
    static bool isInvalidJson(QString &checkContent, QString &analysJson);
    static bool isValidJson(QByteArray checkContent, QJsonDocument *analysJson);

    // 过滤json('')
    static QString filterJsonPre(QString jsonContent);

    // 过滤json('')
    static bool isPathAlreadyExist(QString &path);

};

#endif // TSHELPTOOLS_H
