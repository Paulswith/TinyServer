#ifndef TSGLOBALATTRIBUTE_H
#define TSGLOBALATTRIBUTE_H

#include <QStringList>

namespace GlobalStaticPro {
    // 当前已有path， 区分大小写
    extern QStringList alreadyExistPaths;
}

class TSGlobalAttribute
{
public:
    TSGlobalAttribute();
};

#endif // TSGLOBALATTRIBUTE_H
