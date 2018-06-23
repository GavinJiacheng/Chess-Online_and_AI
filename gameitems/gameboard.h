#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardbox.h"
class possible_boxNpiece;
#include "AI_files/possible_boxnpiece.h"
class findallmovess;
#include "AI_files/findallmovess.h"
class stupid_AI;
#include "AI_files/stupid_ai.h"
#include <vector>

class gameboard
{
public:
    gameboard();
    gameboard(int i);
    ~gameboard();
    void placeBoxes();
    boardbox* getbox(int i, int j);
    void startup();
    int checkCanCheck();
    int playerSside();
    void appendPieces(Piece* P);
    void findPossibleMove(int side);
    std::shared_ptr<possible_boxNpiece> findGoodMovesOneTrun(int side, stupid_AI *SmartGuy);
    void addtoboxes(findallmovess* thing);
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
    std::vector<std::vector<int>> getlocalmap();
    std::vector<std::vector<int>> createloaclmap();
    QList <possible_boxNpiece *> possible_boxNpiece_White;
    QList <possible_boxNpiece *> possible_boxNpiece_Black;
    int oldlocation[2];
    //stupid_ai *Cortana = NULL;
    std::vector<std::vector<int>> loaclmap; //should be smart pointer
private:
    int playerside =0;
    boardbox *boxes[8][8];
    QList <Piece *> white;
    QList <Piece *> black;
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
    int inverse(int i);
};

#endif // GAMEBOARD_H
