#ifndef TSCONSOLE_H
#define TSCONSOLE_H

#include <QTextEdit>
#include "MainClass/AppConfig/TSGlobalAttribute.h"

using namespace AppConfigs;
class TSConsole: public QTextEdit
{
    Q_OBJECT
public:
    TSConsole(QWidget *parent = nullptr);

private:
    void prehandleColorContent(QString& content, PrintType colorType);
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
    void slotWithprint(QString content, PrintType colorType = printStdout);
};

#endif // TSCONSOLE_H

