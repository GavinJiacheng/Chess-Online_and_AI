#ifndef ONLINEMOVE_H
#define ONLINEMOVE_H


class onlineMove
{
public:
    onlineMove(int Fx, int Fy, int Tx, int Ty, int Cast)
    {
        fromX = Fx;
        fromY = Fy;
        ToX = Tx;
        ToY = Ty;
        Castling = Cast;
    }
    int fromX;
    int fromY;
    int ToX;
    int ToY;
    int Castling;
};


#endif // ONLINEMOVE_H
