#ifndef FINDALLMOVESS_H
#define FINDALLMOVESS_H

#include "possible_boxnpiece.h"
#include "moves.h"



class findallmovess
{
public:
    findallmovess(int side, int** map);
    void findMovesFor(int x, int y, int** map);
    QList <moves *> allmoves;
    QList <int **> allmaps;
    int side;
    void kingsmove(int x,int y,int** map);
    void queensmove(int x,int y,int** map);
    void rooksmove(int x,int y,int** map);
    void knightsmove(int x,int y,int** map);
    void bishopsmove(int x,int y,int** map);
    void pawnsmove(int x,int y,int** map);
};

#endif // FINDALLMOVESS_H
