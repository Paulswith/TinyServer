#ifndef TSBODYEDITWIDGET_H
#define TSBODYEDITWIDGET_H

#include <QWidget>
#include "ui_TSBodyEdit_design.h"

enum validBodyEnum{
    NoError,
    pathExistError,
    reqMothodUnMatchError,
    reqJsonInvalidError,
    rspJsonInvalidError
};

class TSBodyEditWidget : public QWidget
{
    Q_OBJECT

public:
    TSBodyEditWidget(QRect geometry, QWidget *parent=nullptr);
    ~TSBodyEditWidget();
    void showViewWindowWithData(const QStringList &data);
    void setUpdateBtnEnable(bool shouldEnable);

signals:
    void signal_windowClose();
    void signal_addNewBody();

private:
    Ui::TSBodyEditWidget *ui;
    QPair<validBodyEnum, QStringList> checkSaveData(bool checkPath=true);  // 检查待写入的数据是否合法
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

    // show tips
    void showTips(const validBodyEnum &enumError);
    // isUpdateBtnEnable
//    bool isUpdateBtnEnable = true;

};

#endif // TSBODYEDITWIDGET_H
