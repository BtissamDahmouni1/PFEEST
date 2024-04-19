#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"
class Pawn : public ChessPiece
{
public:
    Pawn(QString team, QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();

private:
};

#endif // PAWN_H
