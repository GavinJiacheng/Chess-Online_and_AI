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
    bool checkCanCheck();
    int playerSside();
    void appendPieces(Piece* P);
private:
    int playerside =0;
    boardbox *boxes[8][8];
    QList <Piece *> white;
    QList <Piece *> black;
    Piece *WKing;
    Piece *BKing;
    bool Checking;
};

#endif // GAMEBOARD_H
