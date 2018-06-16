#include "rook.h"

rook::rook(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(50*(1-2*color));
}

void rook::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/rook1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/rook.png"));
}

bool rook::canmove(int x, int y)
{
    if (x == location[0] && y != location[1])
    {
        int pace = y - location[1];
        if (pace > 0)
            pace = 1;
        else
            pace = -1;
        for (int i =location[1]+pace; i != y; i+=pace)
            if (this->getCurrentBox()->getboard()->getbox(x,i)->hasPiece())
                return false;
        return true;
    }
    else if (y == location[1] && x != location[0] )
    {
        int pace = x - location[0];
        if (pace > 0)
            pace = 1;
        else
            pace = -1;
        for (int i =location[0]+pace; i != x; i+=pace)
            if (this->getCurrentBox()->getboard()->getbox(i,y)->hasPiece())
                return false;
        return true;
    }
    else
        return false;
}

int rook::getType()
{
    return 7;
}
