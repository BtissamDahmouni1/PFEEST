#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "chesspiece.h"
#include <chessboard.h>
#include "clock.h"
#include <QTextEdit> // Pour l'affichage des messages
#include <QLineEdit> // Pour la saisie des messages
#include <QPushButton> // Pour le bouton d'envoi


class Game : public QGraphicsView
{
    Q_OBJECT
public:

    Game(QWidget *parent = nullptr);

    void drawDeadHolder(int x, int y, QColor color);
    void drawChessBoard();
    void drawChessCoordinates();
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);

    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);


    ChessPiece *pieceToMove;

    QString getTurn();
    void setTurn(QString value);
    void changeTurn();

    ChessBox *collection[8][8];
    QGraphicsTextItem *check;
    QList<ChessPiece *> alivePiece;
    void gameOver();
    void removeAll();
    void resetGame();
    void placeInitialPieces();
public slots:
    void start();
    void onTimeOut();
    void sendMessage();
private:
    QGraphicsScene *gameScene;

    QList<ChessPiece *> whiteDead;
    QList<ChessPiece *> blackDead;
    QGraphicsRectItem *deadHolder;
    QString turn;
    ChessBoard *chess;
    QList<QGraphicsItem *> listG;
    QGraphicsTextItem *turnDisplay;
    Clock *topClock;
    Clock *bottomClock;
    QTextEdit *chatDisplay;
    QLineEdit *messageInput;
    QPushButton *sendButton;




};

#endif // GAME_H
