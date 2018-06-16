#include "bishop.h"

bishop::bishop(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(30*(1-2*color));
}

void bishop::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/bishop1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/bishop.png"));
}

bool bishop::canmove(int x, int y)
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
    else
        return false;
}

int bishop::getType()
{
    return 5;
}


