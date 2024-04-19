#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"
class Queen : public ChessPiece
{
public:
    Queen(QString team, QGraphicsItem *parent = nullptr);
    void setImage();

    void moves();
};

#endif // QUEEN_H
