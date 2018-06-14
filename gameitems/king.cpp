#include "king.h"

king::king(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
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
    if (x - location[0] <= 1 && x - location[0] >= (-1) && y-location[1] <= 1 && y - location[1] >= (-1))
            return true;
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
