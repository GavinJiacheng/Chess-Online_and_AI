#include "pawn.h"

pawn::pawn(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(10*(1-2*color));
}

void pawn::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/pawn1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/pawn.png"));
}

bool pawn::canmove(int x, int y)
{
    int pace = -1 + 2* side;
    if (!Ismoved())
    {
        if (y-location[1] == pace && x == location[0])
        {
            if (this->getCurrentBox()->getboard()->getbox(x,y)->hasPiece())
                return false;
            else
                return true;
        }
        else if(y-location[1] == 2*pace && x == location[0])
        {
            if (this->getCurrentBox()->getboard()->getbox(x,y)->hasPiece())
                return false;
            else if (this->getCurrentBox()->getboard()->getbox(x,y-pace)->hasPiece())
                return false;
            else
                return true;
        }
        else
            return false;
    }else
    {
        if (y-location[1] == pace && x == location[0])
        {
            if (this->getCurrentBox()->getboard()->getbox(x,y)->hasPiece())
                return false;
            else
                return true;
        }
        else
            return false;
    }
}

bool pawn::pawnAttack(int x, int y)
{
    int pace = -1 + 2* side;
    if (y-location[1] == pace && (x - location[0] == 1 || x - location[0] == -1))
        return true;
    else
        return false;
}

int pawn::getType()
{
    return 4;
}

