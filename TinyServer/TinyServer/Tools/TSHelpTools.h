#ifndef TSHELPTOOLS_H
#define TSHELPTOOLS_H

#include <QString>

class TSHelpTools
{
public:
    TSHelpTools();
    // 验证是否为非法JSON
    static bool isInvalidJson(QString &checkContent);

    // 过滤json('')
    static QString filterJsonPre(QString jsonContent);

    // 过滤json('')
    static bool isPathAlreadyExist(QString &path);
};

#endif // TSHELPTOOLS_H
