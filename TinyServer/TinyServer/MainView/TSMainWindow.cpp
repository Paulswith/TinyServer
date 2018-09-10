#include <QThread>
#include <QDebug>
#include <QMouseEvent>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QAbstractSocket>

#include "TSMainWindow.h"
#include "Tools/TSSqlConnection.h"



TSMainWindow::TSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSMainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    connect(this, &TSMainWindow::signal_printToConsole,
            ui->ts_consoleWidget, &TSConsole::showToConsole);

    connect(ui->ts_tabWidget, &QTabWidget::tabBarDoubleClicked, [&](int index){
        qDebug() << "tabBarDoubleClicked: " << index;
        if (index == 1) ui->ts_bodyEditWidget->reloadDataModel();
    });
}

void TSMainWindow::showEvent(QShowEvent *event)
{
    connect(ui->ts_startListen, &QPushButton::clicked, [&](){
        printToConsole("请求开启服务监听！");
    });
// 获取当前IP
    connect(ui->ts_suspendListen, &QPushButton::clicked, [&](){
        printToConsole(currentIp());
    });

    event->accept();
}

QString TSMainWindow::currentIp()
{
    QString t_ip;
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    foreach (QHostAddress ipItem, addresses) {
        if ((ipItem.protocol() == QAbstractSocket::IPv4Protocol)
                &&  (ipItem != QHostAddress::Null)
                && (ipItem != QHostAddress::LocalHost)
                && (ipItem.toString().left(3) == "192")) {
            qDebug() << "Finded-ip: " << ipItem.toString();
            t_ip = ipItem.toString();
        }
    }
    return "+"+t_ip;
}

void TSMainWindow::printToConsole(QString str)
{
    emit signal_printToConsole(str);
}

void TSMainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "all-Windows-close";
    if (bodyEditWidget != nullptr) bodyEditWidget->close(); // 要关一起关
    TSSqlConnection::closeSqlConnection();  // 关闭数据库连接
    event->accept();
}

TSMainWindow::~TSMainWindow()
{
    delete ui;
}
