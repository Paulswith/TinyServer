#ifndef TSLCDCLOCK_H
#define TSLCDCLOCK_H

#include <QLCDNumber>
#include <QWidget>
#include <QTimer>

class TSLCDClock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit TSLCDClock(QWidget *parent = nullptr);

private:
    QTimer *timer;
    void initialTimer();
    void setLCDProperty();
};

#endif // TSLCDCLOCK_H
