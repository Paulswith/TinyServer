#ifndef TSBODYEDITWIDGET_H
#define TSBODYEDITWIDGET_H

#include <QWidget>

namespace Ui {
class TSBodyEditWidget;
}

class TSBodyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TSBodyEditWidget(QWidget *parent = nullptr);
    TSBodyEditWidget(QRect geometry, QWidget *parent = nullptr);

    ~TSBodyEditWidget();

private:
    Ui::TSBodyEditWidget *ui;
};

#endif // TSBODYEDITWIDGET_H
