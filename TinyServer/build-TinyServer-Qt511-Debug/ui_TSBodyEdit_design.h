/********************************************************************************
** Form generated from reading UI file 'TSBodyEdit_design.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSBODYEDIT_DESIGN_H
#define UI_TSBODYEDIT_DESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TSBodyEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *ts_pathHWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *ts_pathTitleLabel;
    QLineEdit *ts_pathEdit;
    QWidget *ts_methodHWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ts_methodTitleLabel;
    QLineEdit *ts_methodEdit;
    QWidget *ts_requestHWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ts_requestTitleLabel;
    QTextEdit *ts_requestEdit;
    QWidget *ts_responseHWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *ts_responseTitleLabel;
    QTextEdit *ts_responseEdit;
    QWidget *ts_commitHWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *ts_commitHLabel;
    QPushButton *ts_commitBtn;

    void setupUi(QWidget *TSBodyEditWidget)
    {
        if (TSBodyEditWidget->objectName().isEmpty())
            TSBodyEditWidget->setObjectName(QStringLiteral("TSBodyEditWidget"));
        TSBodyEditWidget->resize(596, 452);
        verticalLayout = new QVBoxLayout(TSBodyEditWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ts_pathHWidget = new QWidget(TSBodyEditWidget);
        ts_pathHWidget->setObjectName(QStringLiteral("ts_pathHWidget"));
        horizontalLayout = new QHBoxLayout(ts_pathHWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ts_pathTitleLabel = new QLabel(ts_pathHWidget);
        ts_pathTitleLabel->setObjectName(QStringLiteral("ts_pathTitleLabel"));
        ts_pathTitleLabel->setMinimumSize(QSize(65, 0));
        ts_pathTitleLabel->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(ts_pathTitleLabel);

        ts_pathEdit = new QLineEdit(ts_pathHWidget);
        ts_pathEdit->setObjectName(QStringLiteral("ts_pathEdit"));

        horizontalLayout->addWidget(ts_pathEdit);


        verticalLayout->addWidget(ts_pathHWidget);

        ts_methodHWidget = new QWidget(TSBodyEditWidget);
        ts_methodHWidget->setObjectName(QStringLiteral("ts_methodHWidget"));
        horizontalLayout_2 = new QHBoxLayout(ts_methodHWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ts_methodTitleLabel = new QLabel(ts_methodHWidget);
        ts_methodTitleLabel->setObjectName(QStringLiteral("ts_methodTitleLabel"));
        ts_methodTitleLabel->setMinimumSize(QSize(65, 0));
        ts_methodTitleLabel->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(ts_methodTitleLabel);

        ts_methodEdit = new QLineEdit(ts_methodHWidget);
        ts_methodEdit->setObjectName(QStringLiteral("ts_methodEdit"));

        horizontalLayout_2->addWidget(ts_methodEdit);


        verticalLayout->addWidget(ts_methodHWidget);

        ts_requestHWidget = new QWidget(TSBodyEditWidget);
        ts_requestHWidget->setObjectName(QStringLiteral("ts_requestHWidget"));
        horizontalLayout_3 = new QHBoxLayout(ts_requestHWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        ts_requestTitleLabel = new QLabel(ts_requestHWidget);
        ts_requestTitleLabel->setObjectName(QStringLiteral("ts_requestTitleLabel"));
        ts_requestTitleLabel->setMinimumSize(QSize(65, 0));

        horizontalLayout_3->addWidget(ts_requestTitleLabel);

        ts_requestEdit = new QTextEdit(ts_requestHWidget);
        ts_requestEdit->setObjectName(QStringLiteral("ts_requestEdit"));

        horizontalLayout_3->addWidget(ts_requestEdit);


        verticalLayout->addWidget(ts_requestHWidget);

        ts_responseHWidget = new QWidget(TSBodyEditWidget);
        ts_responseHWidget->setObjectName(QStringLiteral("ts_responseHWidget"));
        horizontalLayout_4 = new QHBoxLayout(ts_responseHWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ts_responseTitleLabel = new QLabel(ts_responseHWidget);
        ts_responseTitleLabel->setObjectName(QStringLiteral("ts_responseTitleLabel"));
        ts_responseTitleLabel->setMinimumSize(QSize(65, 0));

        horizontalLayout_4->addWidget(ts_responseTitleLabel);

        ts_responseEdit = new QTextEdit(ts_responseHWidget);
        ts_responseEdit->setObjectName(QStringLiteral("ts_responseEdit"));

        horizontalLayout_4->addWidget(ts_responseEdit);


        verticalLayout->addWidget(ts_responseHWidget);

        ts_commitHWidget = new QWidget(TSBodyEditWidget);
        ts_commitHWidget->setObjectName(QStringLiteral("ts_commitHWidget"));
        horizontalLayout_5 = new QHBoxLayout(ts_commitHWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ts_commitHLabel = new QLabel(ts_commitHWidget);
        ts_commitHLabel->setObjectName(QStringLiteral("ts_commitHLabel"));

        horizontalLayout_5->addWidget(ts_commitHLabel);

        ts_commitBtn = new QPushButton(ts_commitHWidget);
        ts_commitBtn->setObjectName(QStringLiteral("ts_commitBtn"));
        ts_commitBtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(ts_commitBtn);


        verticalLayout->addWidget(ts_commitHWidget);


        retranslateUi(TSBodyEditWidget);

        QMetaObject::connectSlotsByName(TSBodyEditWidget);
    } // setupUi

    void retranslateUi(QWidget *TSBodyEditWidget)
    {
        TSBodyEditWidget->setWindowTitle(QApplication::translate("TSBodyEditWidget", "Form", nullptr));
        ts_pathTitleLabel->setText(QApplication::translate("TSBodyEditWidget", "PATH:", nullptr));
        ts_pathEdit->setPlaceholderText(QApplication::translate("TSBodyEditWidget", "/path/to/request", nullptr));
        ts_methodTitleLabel->setText(QApplication::translate("TSBodyEditWidget", "METHOD:", nullptr));
        ts_methodEdit->setPlaceholderText(QApplication::translate("TSBodyEditWidget", "current open support `POST`", nullptr));
        ts_requestTitleLabel->setText(QApplication::translate("TSBodyEditWidget", "Request:", nullptr));
        ts_requestEdit->setPlaceholderText(QApplication::translate("TSBodyEditWidget", "JSON-format", nullptr));
        ts_responseTitleLabel->setText(QApplication::translate("TSBodyEditWidget", "Response:", nullptr));
        ts_responseEdit->setPlaceholderText(QApplication::translate("TSBodyEditWidget", "JSON-format", nullptr));
        ts_commitHLabel->setText(QString());
        ts_commitBtn->setText(QApplication::translate("TSBodyEditWidget", "Commit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TSBodyEditWidget: public Ui_TSBodyEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSBODYEDIT_DESIGN_H
