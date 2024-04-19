
#include <QApplication>
#include "game.h"
#include "client.h"
Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->start();
    Client joueur;//
    //joueur.connect();//
    joueur.teste();
    return a.exec();
}
