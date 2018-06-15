#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardbox.h"
class possible_boxNpiece;
#include "AI_files/possible_boxnpiece.h"

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
    void findPossibleMove(int side);
    void checkPossiblemove(Piece *P);
    void checkKingsMove(Piece *P);
    void checkQueensMove(Piece *P);
    void checkRooksMove(Piece *P);
    void checkKnightsMove(Piece *P);
    void checkBishopsMove(Piece *P);
    void checkPawnsMove(Piece *P);
    void addPossibleBox(Piece *P,int x,int y);
    void supposeddie(Piece* P);
    void triedPiece(Piece* P);
    void gobackThinking();
    void NosupposedDie();
    int oldlocation[2];
private:
    int playerside =0;
    boardbox *boxes[8][8];
    QList <Piece *> white;
    QList <Piece *> black;
    QList <possible_boxNpiece *> possible_boxNpiece_White;
    QList <possible_boxNpiece *> possible_boxNpiece_Black;
    //QList <possible_boxNpiece *> possible_castling_Black;
    //QList <possible_boxNpiece *> possible_castling_White;
    Piece *WKing;
    Piece *BKing;
    Piece *OldPiece;
    Piece *supposedDiedPiece;
    //Piece *OldROOK;
    //Piece *lastPiece;
    //Piece *lastdiePiece;
    //Piece *lastROOK;
    boardbox *lastbox;
    bool Checking;
};

#endif // GAMEBOARD_H
