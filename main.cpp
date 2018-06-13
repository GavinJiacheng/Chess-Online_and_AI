#include "game.h"
#include <QApplication>

game *Game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game = new game();
    Game->show();
    Game->placeTheBoard();
    Game->placePieces();
    return a.exec();
}
