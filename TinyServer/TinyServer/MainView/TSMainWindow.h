#ifndef TSMAINWINDOW_H
#define TSMAINWINDOW_H

#include <QMainWindow>

#include "TSConsole.h"
#include "PushView/TSBodyEditWidget.h"
#include "Design_Forms/TSWindowDesign.hpp"


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
    bool isMousePressed; // 拖拽的前提是鼠标左键摁住
    QString currentIp(); // 获取当前IP
    void printToConsole(QString str); // 辅助输出到控制

    // 事件处理:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

};

#endif // TSMAINWINDOW_H
