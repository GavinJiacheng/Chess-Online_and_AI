#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight:public Piece
{
public:
    knight(int color, int col, int row,  QGraphicsItem *parent = NULL);
    void setImage();
    bool canmove(int x, int y);
    int getType();
};

#endif // KNIGHT_H
