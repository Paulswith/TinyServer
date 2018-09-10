#ifndef TSMAINWINDOW_H
#define TSMAINWINDOW_H

#include <QMainWindow>

#include "TSConsole.h"
#include "PushView/TSBodyEditWidget.h"
#include "Design_Forms/TSWindowDesign.hpp"
#include "httplistener.h"


class TSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSMainWindow(QWidget *parent = nullptr);
    ~TSMainWindow();
    TSBodyEditWidget *bodyEditWidget;

signals:
    void signal_printToConsole(QString str); // 输出到控制台

private:
    Ui::TSMainWindow *ui;
    QString currentIp(); // 获取当前IP
    void printToConsole(QString str); // 辅助输出到控制

    // 事件处理:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

    // 当前服务器是否开启
    bool isServerListening = false;
    stefanfrings::HttpListener *serverListener;
    void startServerListen();

};

#endif // TSMAINWINDOW_H
