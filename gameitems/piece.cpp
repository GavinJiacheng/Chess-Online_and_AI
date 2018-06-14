#include "piece.h"
#include "game.h"
#include <QDebug>

extern game* Game;
Piece::Piece(int color, int col, int row, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = color;
    location[0] = col;
    location[1] = row;
    CurrentBox = Game->getbox(col, row);
    CurrentBox->placepiece(this);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //this->debug = 89;
    if (event->button() == Qt ::LeftButton && !isdead && Game->getTurn() == this->side)
    {
        if (Game != NULL)
            Game->pickUpPieces(this);
            //qDebug() << Game->piece_to_placed->debug;
    }
}


void Piece::setCurrentBox(boardbox *box)
{
    CurrentBox = box;
}

boardbox *Piece::getCurrentBox()
{
    return CurrentBox;
}

int Piece::die()
{
    if (side)
    {
        int ROW = deadBlack/3;
        int COL = deadBlack - 3*ROW;
        deadBlack++;
        this->setPos(1150+COL*75, 50+ROW*80);
        this->isdead =true;
        this->CurrentBox->removepiece();
        this->CurrentBox =NULL;
    }
    else
    {
        int ROW = deadWhite/3;
        int COL = deadWhite - 3*ROW;
        deadWhite++;
        this->setPos(COL*75, 50+ROW*80);
        this->isdead =true;
        this->CurrentBox->removepiece();
        this->CurrentBox =NULL;
    }
    return -1;
}

void Piece::setWeight(int w)
{
    weight = w;
}

int Piece::getWeight()
{
    return weight;
}

int Piece::getside()
{
    return side;
}

void Piece::setlocation(int x, int y)
{
    location[0] =x;
    location[1] =y;
}

void Piece::moved()
{
    ismoved = true;
}

bool Piece::Ismoved()
{
    return ismoved;
}

bool Piece::dead()
{
    return isdead;
}

bool Piece::pawnAttack(int x, int y)
{
    return false;
}
