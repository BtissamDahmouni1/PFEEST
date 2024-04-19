#ifndef CLOCK_H
#define CLOCK_H

#include <QGraphicsTextItem>
#include <QTimer>

class Clock : public QGraphicsTextItem
{
    Q_OBJECT

public:
    Clock(QGraphicsItem *parent = nullptr);
    void startClock(); // Démarre l'horloge
    void stopClock();  // Arrête l'horloge

public slots:
    void updateClock();
    void resetClock(int minutes, int seconds);
signals:
    void timeOut();

private:
    int seconds;
    int minutes;
    QTimer *timer;
};

#endif // CLOCK_H
