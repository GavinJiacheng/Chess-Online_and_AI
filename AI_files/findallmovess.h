#ifndef FINDALLMOVESS_H
#define FINDALLMOVESS_H

#include "possible_boxnpiece.h"
#include "moves.h"



class findallmovess
{
public:
    findallmovess(int side, int** map);
    void findMovesFor(int x, int y, int** map);
    QList <moves *> allmoves; // same as below

    QList <int **> allmaps; //should be smart pointers, or it will fuck you.
    int side;
    bool checking = false;
    bool isChecked = false;
    void kingsmove(int x,int y,int** map);
    void queensmove(int x,int y,int** map);
    void rooksmove(int x,int y,int** map);
    void knightsmove(int x,int y,int** map);
    void bishopsmove(int x,int y,int** map);
    void pawnsmove(int x,int y,int** map);
    bool attacked(int x, int y, int** map);
    int kingslanding[2];
};

#endif // FINDALLMOVESS_H
