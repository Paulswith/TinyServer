#include "TSBodyEditWidget.h"
#include "Tools/TSSqlConnection.h"

#include <QDebug>
#include <QShowEvent>

TSBodyEditWidget::TSBodyEditWidget(QRect geometry, QWidget *parent)
    :QWidget (parent), ui(new Ui::TSBodyEditWidget)
{
    ui->setupUi(this);
    setGeometry(geometry);
}

void TSBodyEditWidget::showEvent(QShowEvent *event)
{

    connect(ui->ts_commitBtn, &QPushButton::clicked, [&](){

        checkSaveData();
    });
    event->accept();
}

bool TSBodyEditWidget::checkSaveData()
{
    /**
. 新增数据,在点击Commit的时候进行如下检查:
    2.1 检查路径是否存在, 存在则询问放弃, 还是强制覆盖
    2.2 req-rsp, 都进行json语法检查,不通过不给新增
*/
    //        // 检查下是否合法, 合法调用SQL写入
    //        QString path = ui->ts_pathEdit->text();
    //        qDebug() << "query pathExist:"<< path << " ----"
    //                 << TSSqlConnection::isPathInDBsets(path);

    QStringList insertStrs;
    insertStrs.append(ui->ts_pathEdit->text());
    insertStrs.append(ui->ts_methodEdit->text());
    insertStrs.append(ui->ts_requestEdit->toPlainText());
    QString rsp_content = QString("json('%1')").arg(ui->ts_responseEdit->toPlainText());
    insertStrs.append(rsp_content);

    bool suc = TSSqlConnection::insertBodyData(insertStrs);
    qDebug() << "Insert data: " << insertStrs
             << "\t" << suc;

    return false;
}



TSBodyEditWidget::~TSBodyEditWidget()
{
    delete ui;
}
