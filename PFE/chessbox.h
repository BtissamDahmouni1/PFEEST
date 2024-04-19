#ifndef CHESSBOX_H
#define CHESSBOX_H

#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "chesspiece.h"

class ChessPiece;
class ChessBox : public QGraphicsRectItem
{
public:

    ChessBox(QGraphicsItem *parent = nullptr);
    ~ChessBox();


    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(ChessPiece *piece);

    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChessPiece();
    void setHasChessPiece(bool value, ChessPiece *piece = nullptr);

    void checkForCheck();

    QString getChessPieceColor();
    void setChessPieceColor(QString value);

    int rowLoc;
    int colLoc;

    ChessPiece *currentPiece;

private:
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    QString chessPieceColor;
};

#endif // CHESSBOX_H
