#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen:public Piece
{
public:
    queen(int color, int col, int row,  QGraphicsItem *parent = NULL);
    void setImage();
    bool canmove(int x, int y);
    int getType();
};

#endif // QUEEN_H
