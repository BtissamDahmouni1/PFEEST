#include "clock.h"

Clock::Clock(QGraphicsItem *parent) : QGraphicsTextItem(parent), minutes(10), seconds(0)
{
    updateClock();
    setDefaultTextColor(Qt::white);

    setPos(-25, -25);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
    timer->start(1000);
}
void Clock::startClock()
{
    if(!timer->isActive()) {
        timer->start(1000);
    }
}

void Clock::stopClock()
{
    if(timer->isActive()) {
        timer->stop();
    }
}

void Clock::updateClock()
{
    if (minutes == 0 && seconds == 0) {
        emit timeOut();
        timer->stop();
        return;
    }
    QString timeText = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    setPlainText(timeText);

    if (minutes == 0 && seconds == 0) {
        timer->stop();
        return;
    }

    if (seconds == 0) {
        if (minutes > 0) {
            minutes--;
            seconds = 59;
        }
    } else {
        seconds--;
    }
}
void Clock::resetClock(int minutes, int seconds) {
    this->minutes = minutes;
    this->seconds = seconds;
    updateClock();
}


