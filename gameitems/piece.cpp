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
    if (event->button() == Qt ::LeftButton && !isdead)
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

void Piece::die()
{
    if (side)
    {
        deadBlack++;
        int ROW = deadBlack/3;
        int COL = deadBlack - 3*ROW -1;
        this->setPos(1150+COL*70, 50+ROW*80);
        this->isdead =true;
        this->CurrentBox->removepiece();
        this->CurrentBox =NULL;
    }
    else
    {
        deadWhite++;
        int ROW = deadWhite/3;
        int COL = deadWhite - 3*ROW -1;
        this->setPos(COL*70, 50+ROW*80);
        this->isdead =true;
        this->CurrentBox->removepiece();
        this->CurrentBox =NULL;
    }
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
