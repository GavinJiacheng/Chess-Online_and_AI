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
    if (event->button() == Qt ::LeftButton && !isdead && Game->getTurn() == this->side && Game->AIsSide != this->side && (!Game->onlineGame || Game->Lobby->yourSide == this->side))
    {
        if (Game != NULL)
            Game->pickUpPieces(this);
            origin_zValue = this->zValue();
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

void Piece::setdie(bool t)
{
    isdead = t;
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

int Piece::getCol()
{
    return location[0];
}

int Piece::getRow()
{
    return location[1];
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

void Piece::moveTo(int x, int y)
{
    int xPos, yPos;
    if(this->getCurrentBox()->getboard()->playerSside())
    {
        xPos = (10-x)*100;
        yPos = 750-y*100;
    }
    else
    {
        xPos = (x+3)*100;
        yPos = y*100+50;
    }
    boardbox *targetBox = this->getCurrentBox()->getboard()->getbox(x,y);
    this->setPos(xPos,yPos);
    this->setlocation(x,y);
    this->moved();
    this->getCurrentBox()->removepiece();
    this->setCurrentBox(targetBox);
    this->getCurrentBox()->placepiece(this);
}

void Piece::tryToMoveTo(int x, int y)
{
    boardbox *targetBox = this->getCurrentBox()->getboard()->getbox(x,y);
    targetBox->getboard()->NosupposedDie();
    if (targetBox->hasPiece())
    {
        targetBox->getpiece()->setdie(true);
        targetBox->getboard()->supposeddie(targetBox->getpiece());
    }
    int oldx = this->getCol();
    int oldy = this->getRow();
    targetBox->getboard()->triedPiece(this);
    this->getCurrentBox()->getboard()->oldlocation[0] = oldx;
    this->getCurrentBox()->getboard()->oldlocation[1] = oldy;
    this->setlocation(x,y);
    this->getCurrentBox()->removepiece();
    this->setCurrentBox(targetBox);
    this->getCurrentBox()->placepiece(this);
}

void Piece::Reset_DeadPieces()
{
    deadBlack = 0;
    deadWhite = 0;
}
