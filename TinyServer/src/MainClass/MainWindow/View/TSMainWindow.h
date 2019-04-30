#ifndef TSMAINWINDOW_H
#define TSMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "TSConsole.h"
#include "TSWindowDesign.hpp"
#include "httplistener.h"
#include "MainClass/Network/TSNetWork.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"

using AppConfigs::PrintType;
class TSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSMainWindow(QWidget *parent = nullptr);
    ~TSMainWindow();

signals:
    void signalWithPrintToConsole(QString str, PrintType printTyle = printStdout); // 输出到控制台

private: /* events */
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

private: /* properties */
    QTimer *statusTimer = nullptr;
    Ui::TSMainWindow *ui;
    TSNetWork *network = nullptr;
    //  timer color at current idnex flag
    quint16 timerCurrentIndex = 0;

private: /* ui-handle */
    void setupWidget();
    void initialTimer();
    void startStatusColorShow();
    QStringList statuColorSheets = {"QLabel {background-color:rgb(154,255,154);}",
                                    "QLabel {background-color:rgb(0,205,0);}",
                                    "QLabel {background-color:rgb(0,139,69);}"};

private: /* custom-methods */
    /* signal handling */
    void connectAllSignals();
    /* server handling */
    void startServerListen();
    void suspendServerListen();
    /* color shining with timer */
};

#endif // TSMAINWINDOW_H
