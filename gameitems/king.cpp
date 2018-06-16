#include "king.h"

king::king(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(900*(1-2*color));
}

void king::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/king1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/king.png"));
}

bool king::canmove(int x, int y)
{
    boardbox *box = this->getCurrentBox()->getboard()->getbox((7+(x-6)*7/4),y);
    Piece* isrook = NULL;
    if (box)
        isrook = box->getpiece();
    if (x - location[0] <= 1 && x - location[0] >= (-1) && y-location[1] <= 1 && y - location[1] >= (-1))
            return true;
    else if (!this->Ismoved() && y == location[1] && (x == 6 || x == 2) && isrook && isrook->getType() == 7 && !isrook->Ismoved())
    {
        int pace = -1 + (x-2)/2;
        if (CurrentBox->checkAttacked(side))
            return false;
        int checkFORCheck = location[0]+pace+pace+pace;
        for (int i = location[0]+pace; i!= (7+(x-6)*7/4); i+=pace)
        {
            //qDebug() << "i = " <<i <<"end = "<<(7+(x-6)*7/4);
            if(i!=checkFORCheck)
                if (this->getCurrentBox()->getboard()->getbox(i,y)->checkAttacked(side))
                        return false;
            if(this->getCurrentBox()->getboard()->getbox(i,y)->hasPiece())
                return false;
        }
        isrook -> moveTo(x-pace, y);
        return true; // uhhhhh, forget to make this outside, fuck.
    }
    else
        return false;
}

int king::die()
{
    this->Piece::die();
    return side;
}

int king::getType()
{
    return 9;
}
