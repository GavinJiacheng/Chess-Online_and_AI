#include "boardbox.h"


boardbox::boardbox(int Col,int Row, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    row = Row;
    col = Col;
    if ((row+col)%2 == 0)
        color = QColor(238,238,210);
    else
        color = QColor(118,150,86);
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    currentPiece = NULL;
}

void boardbox::resetcolor()
{
    brush.setColor(color);
    setBrush(color);
}


void boardbox::placepiece(Piece *newPiece)
{
    currentPiece = newPiece;
}



void boardbox::removepiece()
{
    currentPiece = NULL;
}

bool boardbox::hasPiece()
{
    if (currentPiece != NULL)
        return true;
    else
        return false;
}

void boardbox::setboard(gameboard *board)
{
    this->board = board;
}

gameboard *boardbox::getboard()
{
    return board;
}

Piece *boardbox::getpiece()
{
    return currentPiece;
}
