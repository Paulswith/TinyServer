/********************************************************************************
** Form generated from reading UI file 'TS_design.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TS_DESIGN_H
#define UI_TS_DESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "MainView/TSConsole.h"
#include "MainView/TSBodiesTableView.h"

QT_BEGIN_NAMESPACE

class Ui_TSMainWindow
{
public:
    QWidget *ts_centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *ts_topHolderWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *ts_connectionManagerWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *ts_hanlderBtnsWidgeth;
    QHBoxLayout *horizontalLayout;
    QPushButton *ts_startListen;
    QPushButton *ts_suspendListen;
    QWidget *ts_connectionInfoWidgeth;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ts_connectTitleLabel;
    QLabel *ts_connectionInfoLabel;
    QWidget *ts_showADWidget;
    QLabel *ts_adLabel;
    QTabWidget *ts_tabWidget;
//    QWidget *ts_consoleWidget;
    TSConsole *ts_consoleWidget;
//    QWidget *ts_bodyEditWidget;
    TSBodiesTableView *ts_bodyEditWidget;
    QStatusBar *ts_statusBar;

    void setupUi(QMainWindow *TSMainWindow)
    {
        if (TSMainWindow->objectName().isEmpty())
            TSMainWindow->setObjectName(QStringLiteral("TSMainWindow"));
        TSMainWindow->resize(706, 522);
        ts_centralWidget = new QWidget(TSMainWindow);
        ts_centralWidget->setObjectName(QStringLiteral("ts_centralWidget"));
        verticalLayout = new QVBoxLayout(ts_centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(7, 0, 0, 0);
        ts_topHolderWidget = new QWidget(ts_centralWidget);
        ts_topHolderWidget->setObjectName(QStringLiteral("ts_topHolderWidget"));
        ts_topHolderWidget->setMinimumSize(QSize(0, 120));
        horizontalLayout_3 = new QHBoxLayout(ts_topHolderWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ts_connectionManagerWidget = new QWidget(ts_topHolderWidget);
        ts_connectionManagerWidget->setObjectName(QStringLiteral("ts_connectionManagerWidget"));
        ts_connectionManagerWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(ts_connectionManagerWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        ts_hanlderBtnsWidgeth = new QWidget(ts_connectionManagerWidget);
        ts_hanlderBtnsWidgeth->setObjectName(QStringLiteral("ts_hanlderBtnsWidgeth"));
        horizontalLayout = new QHBoxLayout(ts_hanlderBtnsWidgeth);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 7, 0, 7);
        ts_startListen = new QPushButton(ts_hanlderBtnsWidgeth);
        ts_startListen->setObjectName(QStringLiteral("ts_startListen"));
        ts_startListen->setStyleSheet(QStringLiteral("QPushButton {color:rgb(51,161,201);}\
                                                      QPushButton:pressed{color:rgb(170, 0, 0);}\
                                                      QPushButton:!enabled {background-color:#ff0000;}"));

        horizontalLayout->addWidget(ts_startListen);

        ts_suspendListen = new QPushButton(ts_hanlderBtnsWidgeth);
        ts_suspendListen->setObjectName(QStringLiteral("ts_suspendListen"));
        ts_suspendListen->setStyleSheet("QPushButton{color:rgb(51,161,201);} QPushButton:pressed {color:rgb(170,0,0);}");


        horizontalLayout->addWidget(ts_suspendListen);


        verticalLayout_2->addWidget(ts_hanlderBtnsWidgeth);

        ts_connectionInfoWidgeth = new QWidget(ts_connectionManagerWidget);
        ts_connectionInfoWidgeth->setObjectName(QStringLiteral("ts_connectionInfoWidgeth"));
        ts_connectionInfoWidgeth->setStyleSheet(QStringLiteral("QWidget {background:rgb(233,233,199)}"));
        horizontalLayout_2 = new QHBoxLayout(ts_connectionInfoWidgeth);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 7, 0, 7);
        ts_connectTitleLabel = new QLabel(ts_connectionInfoWidgeth);
        ts_connectTitleLabel->setObjectName(QStringLiteral("ts_connectTitleLabel"));
        ts_connectTitleLabel->setMinimumSize(QSize(0, 0));
        ts_connectTitleLabel->setMaximumSize(QSize(110, 110));
        ts_connectTitleLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ts_connectTitleLabel);

        ts_connectionInfoLabel = new QLabel(ts_connectionInfoWidgeth);
        ts_connectionInfoLabel->setObjectName(QStringLiteral("ts_connectionInfoLabel"));
        ts_connectionInfoLabel->setMinimumSize(QSize(110, 0));
        ts_connectionInfoLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ts_connectionInfoLabel);


        verticalLayout_2->addWidget(ts_connectionInfoWidgeth);
        horizontalLayout_3->addWidget(ts_connectionManagerWidget);

        ts_showADWidget = new QWidget(ts_topHolderWidget);
        auto adHlayout = new QHBoxLayout(ts_showADWidget);
        ts_showADWidget->setObjectName(QStringLiteral("ts_showADWidget"));
        ts_showADWidget->setStyleSheet(QStringLiteral("QWidget {background:rgb(189,252,201);}"));
        ts_adLabel = new QLabel(QString("广告位招租"));
        ts_adLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(20);
        ts_adLabel->setFont(font);
        adHlayout->addWidget(ts_adLabel);

        horizontalLayout_3->addWidget(ts_showADWidget);


        verticalLayout->addWidget(ts_topHolderWidget);

        ts_tabWidget = new QTabWidget(ts_centralWidget);
        ts_tabWidget->setObjectName(QStringLiteral("ts_tabWidget"));
        ts_tabWidget->setStyleSheet(QStringLiteral("QTabWidget::tab-bar { left:10px; } "));
        ts_tabWidget->setTabPosition(QTabWidget::South);
        ts_tabWidget->setTabShape(QTabWidget::Rounded);
        ts_tabWidget->setIconSize(QSize(12, 12));
        ts_tabWidget->setElideMode(Qt::ElideRight);
//        ts_tabWidget->setTabBarAutoHide(true);
//        ts_consoleWidget = new QWidget();
//        ts_consoleWidget->setObjectName(QStringLiteral("ts_consoleWidget"));
//        ts_consoleWidget->setStyleSheet(QStringLiteral(""));
        ts_consoleWidget = new TSConsole();

        ts_tabWidget->addTab(ts_consoleWidget, QString());
//        ts_bodyEditWidget = new QWidget();
//        ts_bodyEditWidget->setObjectName(QStringLiteral("ts_bodyEditWidget"));
        ts_bodyEditWidget = new TSBodiesTableView();
        ts_tabWidget->addTab(ts_bodyEditWidget, QString());

        verticalLayout->addWidget(ts_tabWidget);

        TSMainWindow->setCentralWidget(ts_centralWidget);
        ts_statusBar = new QStatusBar(TSMainWindow);
        ts_statusBar->setObjectName(QStringLiteral("ts_statusBar"));
        TSMainWindow->setStatusBar(ts_statusBar);

        retranslateUi(TSMainWindow);

        ts_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TSMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TSMainWindow)
    {
        TSMainWindow->setWindowTitle(QApplication::translate("TSMainWindow", "TSMainWindow", nullptr));
        ts_startListen->setText(QApplication::translate("TSMainWindow", "\345\274\200\345\220\257\347\233\221\345\220\254", nullptr));
        ts_suspendListen->setText(QApplication::translate("TSMainWindow", "\345\201\234\346\255\242\347\233\221\345\220\254", nullptr));
        ts_connectTitleLabel->setText(QApplication::translate("TSMainWindow", "Connection-info:", nullptr));
        ts_connectionInfoLabel->setText(QString());
        ts_tabWidget->setTabText(ts_tabWidget->indexOf(ts_consoleWidget), QApplication::translate("TSMainWindow", "Console", nullptr));
        ts_tabWidget->setTabText(ts_tabWidget->indexOf(ts_bodyEditWidget), QApplication::translate("TSMainWindow", "Bodies", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TSMainWindow: public Ui_TSMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TS_DESIGN_H
