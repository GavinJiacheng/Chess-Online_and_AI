#include "knight.h"

knight::knight(int color, int col, int row, QGraphicsItem *parent):Piece(color, col, row, parent)
{
    setImage();
    this->Piece::setWeight(30*(1-2*color));
}

void knight::setImage()
{
    if(side)
        setPixmap(QPixmap(":/Images/piecesicon/knight1.png"));
    else
        setPixmap(QPixmap(":/Images/piecesicon/knight.png"));
}

bool knight::canmove(int x, int y)
{
    int dx = x - location[0];
    int dy = y - location[1];
    bool Yis_doubleX = (dy == 2*dx || -dy == 2*dx) && (dx == 1 || dx == (-1));
    bool Xis_doubleY = (dx == 2*dy || -dx == 2*dy) && (dy == 1 || dy == (-1));
    if (Yis_doubleX || Xis_doubleY)
        return true;
    else
        return false;
}

int knight::getType()
{
    return 6;
}
