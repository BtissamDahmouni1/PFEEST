#include "chessbox.h"
#include <QDebug>
#include "game.h"
#include "king.h"

extern Game *game;
ChessBox::ChessBox(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setRect(0, 0, 75, 75);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = nullptr;
}
ChessBox::~ChessBox()
{
    delete this;
}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
// verifier si il existe une piece a deplacer
    if (currentPiece == game->pieceToMove && currentPiece) {
        currentPiece->mousePressEvent(event);
        return;
    }
    if (game->pieceToMove) {
        //verifier si la piece que je veux le deplaacer a meme couleur de le jouer a le tour de jouer
        if (this->getChessPieceColor() == game->pieceToMove->getSide())
            return;
        QList<ChessBox *> movLoc = game->pieceToMove->moveLocation();
        int check = 0;
        for (size_t i = 0, n = static_cast<size_t>(movLoc.size()); i < n; i++) {
            if (movLoc[static_cast<int>(i)] == this) {
                check++;
            }
        }
        if (check == 0)
            return;
        game->pieceToMove->decolor();
        game->pieceToMove->firstMove = false;
        if (this->getHasChessPiece()) {
            this->currentPiece->setIsPlaced(false);
            this->currentPiece->setCurrentBox(nullptr);
            ///ta2akod
            game->placeInDeadPlace(this->currentPiece);
        }
        game->pieceToMove->getCurrentBox()->setHasChessPiece(false);
        game->pieceToMove->getCurrentBox()->currentPiece = nullptr;
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        placePiece(game->pieceToMove);
        game->pieceToMove = nullptr;
        //changing turn
        game->changeTurn();
        checkForCheck();
    }
    else if (this->getHasChessPiece()) {
        this->currentPiece->mousePressEvent(event);
    }
}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void ChessBox::placePiece(ChessPiece *piece)
{
    int caseSize = 75; // Taille de la case
    int pieceWidth = piece->pixmap().width();
    int pieceHeight = piece->pixmap().height();
    int xOffset = (caseSize - pieceWidth) / 2;
    int yOffset = (caseSize - pieceHeight) / 2;

    piece->setPos(x() + xOffset, y() + yOffset);

    piece->setCurrentBox(this);
    setHasChessPiece(true, piece);
    currentPiece = piece;
}

void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}

void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool ChessBox::getHasChessPiece()
{
    return hasChessPiece;
}

void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if (value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}
QString ChessBox::getChessPieceColor()
{
    return chessPieceColor;
}

void ChessBox::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}

//detection de l'echec
void ChessBox::checkForCheck()
{
    int c = 0;
    QList<ChessPiece *> pList = game->alivePiece;
    for (size_t i = 0, n = static_cast<size_t>(pList.size()); i < n; i++) {
        King *p = dynamic_cast<King *>(pList[static_cast<int>(i)]);
        if (p) {
            continue;
        }
        pList[static_cast<int>(i)]->moves();
        pList[static_cast<int>(i)]->decolor();
        QList<ChessBox *> bList = pList[static_cast<int>(i)]->moveLocation();
        for (size_t j = 0, n = static_cast<size_t>(bList.size()); j < n; j++) {
            King *p = dynamic_cast<King *>(bList[static_cast<int>(j)]->currentPiece);
            if (p) {
                if (p->getSide() == pList[static_cast<int>(i)]->getSide())
                    continue;
                bList[static_cast<int>(j)]->setColor(Qt::blue);
                pList[static_cast<int>(i)]->getCurrentBox()->setColor(Qt::darkRed);
                if (!game->check->isVisible())
                    game->check->setVisible(true);
                else {
                    bList[static_cast<int>(j)]->resetOriginalColor();
                    pList[static_cast<int>(i)]->getCurrentBox()->resetOriginalColor();
                    game->gameOver();
                }
                c++;
            }
        }
    }
    if (!c) {
        game->check->setVisible(false);
        for (size_t i = 0, n = static_cast<size_t>(pList.size()); i < n; i++)
            pList[static_cast<int>(i)]->getCurrentBox()->resetOriginalColor();
    }
}
