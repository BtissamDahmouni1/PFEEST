
#include "button.h"
#include <QBrush>
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{

    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);


    text = new QGraphicsTextItem(name, this);
    int xPos = static_cast<int>(rect().width() / 2 - text->boundingRect().width() / 2);
    int yPos = static_cast<int>(rect().height() / 2 - text->boundingRect().height() / 2);
    text->setPos(xPos, yPos);
    text->setDefaultTextColor(Qt::white);


   setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event)
        emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    if (event) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::green);
        setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

    if (event) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::black);
        setBrush(brush);
    }
}

