#include "chessboard.h"
#include "chessbox.h"
#include "bishop.h"
#include "game.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
extern Game *game;
ChessBoard::ChessBoard()
{
    setUpBlack();
    setUpWhite();
}
void ChessBoard::drawBoxes(int x, int y)
{
    int SHIFT = 75;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x + SHIFT * j, y + SHIFT * i);
            if ((i + j) % 2 == 0)
                box->setOriginalColor(QColor("#EEEED5"));//baj clair
            else
                box->setOriginalColor(QColor("#7D945D"));//khdr
            game->addToScene(box);
        }
    }
}
void ChessBoard::addChessPiece()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ChessBox *box = game->collection[i][j];
            if (i < 2) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if (i > 5) {
                static int h;
                box->placePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->addToScene(white[h++]);
            }
        }
    }
}
void ChessBoard::setUpWhite()
{
    ChessPiece *piece;
    for (int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        white.append(piece);
    }
    piece = new Rook("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Queen("WHITE");
    white.append(piece);
    piece = new King("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Rook("WHITE");
    white.append(piece);
}

void ChessBoard::setUpBlack()
{
    ChessPiece *piece;
    piece = new Rook("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Queen("BLACK");
    black.append(piece);
    piece = new King("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Rook("BLACK");
    black.append(piece);
    for (int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        black.append(piece);
    }
}
void ChessBoard::reset()
{
    int k = 0;
    int h = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ChessBox *box = game->collection[i][j];
            box->setHasChessPiece(false);
            box->setChessPieceColor("NONE");
            box->currentPiece = nullptr;
            if (i < 2) {
                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);
            }
            if (i > 5) {
                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);
            }
        }
    }
}
