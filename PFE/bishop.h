#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
class Bishop : public ChessPiece
{
public:
    Bishop(QString team, QGraphicsItem *parent = nullptr);
    void setImage();

    void moves();
};

#endif // BISHOP_H
