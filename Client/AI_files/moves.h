#ifndef MOVES_H
#define MOVES_H

class moves
{
public:
    moves(int P, int Fx, int Fy, int Tx, int Ty, int D)
    {
        piece = P;
        fromX = Fx;
        fromY = Fy;
        ToX = Tx;
        ToY = Ty;
        die = D;
    }
    int piece;
    int fromX;
    int fromY;
    int ToX;
    int ToY;
    int die;
};

#endif // MOVES_H
