#ifndef TSMAINWINDOW_H
#define TSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TSMainWindow;
}

class TSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSMainWindow(QWidget *parent = 0);
    ~TSMainWindow();

private:
    Ui::TSMainWindow *ui;
};

#endif // TSMAINWINDOW_H
