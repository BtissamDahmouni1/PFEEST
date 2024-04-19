#include "game.h"
#include <QDebug>
#include <QPixmap>
#include "button.h"
#include "king.h"
#include "clock.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0, 0, 1500, 950);
    setMinimumSize(1400, 700);
    setMaximumSize(1500, 900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    setBackgroundBrush(brush);
    pieceToMove = nullptr;

    topClock = new Clock();
    bottomClock = new Clock();

    connect(topClock, SIGNAL(timeOut()), this, SLOT(onTimeOut()));
    connect(bottomClock, SIGNAL(timeOut()), this, SLOT(onTimeOut()));

    topClock->resetClock(10, 0);
    bottomClock->resetClock(10, 0);

    topClock->stopClock();
    bottomClock->stopClock();

    topClock->setPos(width() / 2 - 250, 135);
    bottomClock->setPos(width() / 2 - 250, 800);

    check = new QGraphicsTextItem();
    check->setPos(width() / 2 - 100, 10);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::white);
    check->setFont(QFont("", 18));
    check->setVisible(false);
    setTurn("WHITE");
    // Initialisation de la zone de chat
    setAlignment(Qt::AlignCenter);

    int chatWidth = 280;
    int chatHeight = 280;
    int inputWidth = 220;
    int inputHeight = 30;
    int buttonWidth = 55;
    int buttonHeight = 30;
    int rightMargin = 10; // Marge à droite de l'écran
    int bottomMargin = 10; // Marge en bas de l'écran

    // Assurez-vous que ces dimensions sont ajustées si la vue est redimensionnable
    int chatX = this->width() - chatWidth - rightMargin;
    int inputX = this->width() - inputWidth - buttonWidth - 2 * rightMargin; // Pour laisser de l'espace pour le bouton à côté
    int buttonX = this->width() - buttonWidth - rightMargin;

    // Ajustez la position Y en fonction de la hauteur de la scène
    int inputY = this->height() - inputHeight - bottomMargin;
    int buttonY = inputY; // Le bouton est aligné avec la zone de saisie
    int chatY = this->height() - chatHeight - inputHeight - 2 * bottomMargin; // Pour laisser de l'espace au-dessus pour la zone de saisie et le bouton
    // Initialisation de la zone de chat sur le côté droit
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setGeometry(chatX, chatY, chatWidth, chatHeight);

    messageInput = new QLineEdit(this);
    messageInput->setGeometry(inputX, inputY, inputWidth, inputHeight);

    sendButton = new QPushButton("Envoyer", this);
    sendButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Connecter le bouton d'envoi au slot correspondant
    connect(sendButton, &QPushButton::clicked, this, &Game::sendMessage);


}

void Game::drawChessBoard() {
    int caseSize = 75;
    int borderSize = 10;
    int startX = (1500 - 8 * caseSize) / 2;
    int startY = (950 - 8 * caseSize) / 2;

    QPen borderPen(Qt::white);
    borderPen.setWidth(borderSize);
    QGraphicsRectItem* boardBorder = new QGraphicsRectItem(startX - borderSize / 2, startY - borderSize / 2, 8 * caseSize + borderSize, 8 * caseSize + borderSize);
    boardBorder->setPen(borderPen);
    gameScene->addItem(boardBorder);

    chess = new ChessBoard();
    chess->drawBoxes(startX, startY);

    drawChessCoordinates();

    addToScene(topClock);
    addToScene(bottomClock);
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    if (piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        King *g = dynamic_cast<King *>(piece);
        if (g) {
            check->setPlainText("Black Won");
            check->setVisible(true);
             gameOver();
        }
        piece->setVisible(false);
    } else {
        blackDead.append(piece);
        King *g = dynamic_cast<King *>(piece);
        if (g) {
             check->setPlainText("White Won");
             check->setVisible(true);
             gameOver();
        }
        piece->setVisible(false);
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);
}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;

    if(turn == "WHITE") {
        bottomClock->startClock();
        topClock->stopClock();
    } else if(turn == "BLACK") {
        topClock->startClock();
        bottomClock->stopClock();
    }
}

void Game::changeTurn()
{
    if (getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
}

void Game::start()
{
    drawChessBoard();
    for (size_t i = 0, n = static_cast<size_t>(listG.size()); i < n; i++)
        removeFromScene(listG[static_cast<int>(i)]);

    addToScene(check);
    chess->addChessPiece();
}
void Game::gameOver()
{
    setTurn("WHITE");
    alivePiece.clear();
    chess->reset();
    topClock->resetClock(10, 0);
    bottomClock->resetClock(10, 0);
}


void Game::removeAll()
{
    QList<QGraphicsItem *> itemsList = gameScene->items();
    for (size_t i = 0, n = static_cast<size_t>(itemsList.size()); i < n; i++) {
        if (itemsList[static_cast<int>(i)] != check)
            removeFromScene(itemsList[static_cast<int>(i)]);
    }
}

void Game::drawChessCoordinates() {
    int caseSize = 75;
    int borderSize = 20;
    int startX = (1500 - 8 * caseSize) / 2;
    int startY = (950 - 8 * caseSize) / 2;

    for (int i = 0; i < 8; i++) {
        QGraphicsTextItem* number = new QGraphicsTextItem(QString::number(8 - i));
        number->setPos(startX - 2 * borderSize, startY + i * caseSize + caseSize / 2 - number->boundingRect().height() / 2);
        gameScene->addItem(number);
    }

    QStringList alphabet = {"a", "b", "c", "d", "e", "f", "g", "h"};
    for (int i = 0; i < 8; i++) {
        QGraphicsTextItem* letter = new QGraphicsTextItem(alphabet.at(i));
        letter->setPos(startX + i * caseSize + caseSize / 2 - letter->boundingRect().width() / 2, startY + 8 * caseSize + borderSize / 2);
        gameScene->addItem(letter);
    }
}
void Game::onTimeOut()
{
    if (getTurn() == "WHITE") {
        check->setPlainText("Black Won");
        check->setVisible(true);
    } else {
        check->setPlainText("White Won");
        check->setVisible(true);
    }
    gameOver();
}

void Game::sendMessage() {
    QString message = messageInput->text().trimmed();
    if (!message.isEmpty()) {
        chatDisplay->append(">"+ message); // Affiche le message dans la zone de chat
        messageInput->clear();
    }
}
