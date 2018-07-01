#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class rook:public Piece
{
public:
    rook(int color, int col, int row,  QGraphicsItem *parent = NULL);
    void setImage();
    bool canmove(int x, int y);
    int getType();
};

#endif // ROOK_H
