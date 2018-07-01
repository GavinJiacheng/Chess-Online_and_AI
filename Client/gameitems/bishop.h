#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop:public Piece
{
public:
    bishop(int color, int col, int row,  QGraphicsItem *parent = NULL);
    void setImage();
    bool canmove(int x, int y);
    int getType();
};

#endif // BISHOP_H
