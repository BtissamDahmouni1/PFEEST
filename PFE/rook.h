#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"
class Rook : public ChessPiece
{
public:
    Rook(QString team, QGraphicsItem *parent = nullptr);

    void setImage();
    void moves();
};

#endif // ROOK_H
