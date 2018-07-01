#ifndef KING_H
#define KING_H

#include "piece.h"

class king:public Piece
{
public:
    king(int color, int col, int row,  QGraphicsItem *parent = NULL);
    void setImage();
    bool canmove(int x, int y);
    int die();
    int getType();
};

#endif // KING_H
