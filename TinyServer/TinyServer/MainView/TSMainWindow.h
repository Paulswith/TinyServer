#ifndef TSMAINWINDOW_H
#define TSMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

    // 状态色策略
    void startStatusColorShow();
    QStringList statuColorSheets = {"QLabel {background-color:rgb(154,255,154);}",
                                    "QLabel {background-color:rgb(0,205,0);}",
                                    "QLabel {background-color:rgb(0,139,69);}"};
    quint8 cur_color_index = 0;
    QTimer *statusTimer;
};

#endif // TSMAINWINDOW_H
