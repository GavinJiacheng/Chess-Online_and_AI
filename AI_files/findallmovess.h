#ifndef FINDALLMOVESS_H
#define FINDALLMOVESS_H

#include "possible_boxnpiece.h"
#include "moves.h"
#include <vector>
#include <memory>


class findallmovess
{
public:
    findallmovess(int side, std::vector<std::vector<int>> map);
    //don;t need destroctor since we use smart pointers.
    void findMovesFor(int x, int y);
    QList <std::shared_ptr<moves>> allmoves; // same as below

    QList <std::vector<std::vector<int>>> allmaps; //should be smart pointers, or it will fuck you.
    int side;
    bool checking = false;
    bool isChecked = false;
    int map[8][8];
    void kingsmove(int x,int y);
    void queensmove(int x,int y);
    void rooksmove(int x,int y);
    void knightsmove(int x,int y);
    void bishopsmove(int x,int y);
    void pawnsmove(int x,int y);
    bool attacked(int x, int y, std::vector<std::vector<int>> map);
    int kingslanding[2];
};

#endif // FINDALLMOVESS_H
