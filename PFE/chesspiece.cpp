
#include "chesspiece.h"
#include <QDebug>
#include "game.h"
#include "king.h"

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if (this == game->pieceToMove) {
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
        return;
    }
    if ((!getIsPlaced()) || ((game->getTurn() != this->getSide()) && (!game->pieceToMove)))
        return;
    //selecting
    if (!game->pieceToMove) {
        game->pieceToMove = this;
       game->pieceToMove->getCurrentBox()->setColor(Qt::red);
        game->pieceToMove->moves();
    }
    else if (this->getSide() != game->pieceToMove->getSide()) {
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void ChessPiece::setCurrentBox(ChessBox *box)
{
    currentBox = box;
}

ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}

QString ChessPiece::getSide()
{
    return side;
}

void ChessPiece::setSide(QString value)
{
    side = value;
}

bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}

void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;
}
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
void ChessPiece::decolor()
{
    for (size_t i = 0, n = static_cast<size_t>(location.size()); i < n; i++) {
        location[static_cast<int>(i)]->resetOriginalColor();
    }
}

bool ChessPiece::boxSetting(ChessBox *box)
{
    if (box->getHasChessPiece()) {
        King *q = dynamic_cast<King *>(location.last()->currentPiece);
        if (q) {
            box->setColor(Qt::blue);
        } else
            box->setColor(Qt::red);
        return true;
    } else
        location.last()->setColor(Qt::darkRed);
    return false;
}
