#ifndef TSCONFIGUTIL_H
#define TSCONFIGUTIL_H

#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>

//QString const sqlFilenameSuffix = "/Other/data.db";
//QString const configSuffix = "/Other/config.ini";
QString const sqlFilenameSuffix_debug = "/TinyServer/Other/data.db";
QString const configSuffix_debug = "/TinyServer/Other/config.ini";

class TSConfigUtil : public QObject
{
public:
    // debug模式不是真实路径目录:
    static inline QString getDatabasePath() {return queryPath(sqlFilenameSuffix_debug);}
    static inline QString getConfigPath() {return queryPath(configSuffix_debug);}

private:
    static QString queryPath(QString searchFileSuffix){
        // linux_debug
//        return QString("/home/dobby/Code/Cpp/TinyServer/TinyServer/TinyServer/Other/data.db");

        QString binPath = QCoreApplication::applicationDirPath();
        quint8 deep = 0;
        QFile searchFile;
        bool isSearchFileExist = false; // 是否找到路径了
        QString parentStr = "/..";
        QString centerStr = "";
        do{
            centerStr += parentStr;
            searchFile.setFileName(binPath+ centerStr + searchFileSuffix);
            qDebug() << "searchFile: " << searchFile.fileName();
            if (searchFile.exists()){
                isSearchFileExist = true;
                break;
            }
            deep ++;
        }while(deep < 5);  // 往父目录最深搜索路径

        if (!isSearchFileExist) {
            return QString("");
        }
        return QDir(searchFile.fileName()).canonicalPath();
    }
};

#endif // TSCONFIGUTIL_H
