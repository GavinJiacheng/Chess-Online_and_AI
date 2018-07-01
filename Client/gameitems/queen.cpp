#include "queen.h"

queen::queen(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(90*(1-2*color));
}

void queen::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/queen1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/queen.png"));
}

bool queen::canmove(int x, int y)
{
    if((x - location[0] == y - location[1] || x - location[0] == location[1] - y) && x - location[0] != 0)
    {
        int Xpace = x -location[0];
        int Ypace = y -location[1];
        if (Xpace > 0)
            Xpace = 1;
        else
            Xpace = -1;
        if (Ypace > 0)
            Ypace = 1;
        else
            Ypace = -1;
        int i = location[0]+Xpace;
        int j = location[1]+Ypace;
        for (; i!=x; i +=Xpace)
        {
            if (this->getCurrentBox()->getboard()->getbox(i,j)->hasPiece())
                return false;
            else
                j += Ypace;
        }
        return true;
    }
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

int queen::getType()
{
    return 8;
}
