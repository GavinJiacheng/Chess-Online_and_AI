#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardbox.h"


class gameboard
{
public:
    gameboard();
    ~gameboard();
    void placeBoxes();
    boardbox* getbox(int i, int j);
    void startup();
private:
    boardbox *boxes[8][8];
    QList <Piece *> white;
    QList <Piece *> black;
};

#endif // GAMEBOARD_H
