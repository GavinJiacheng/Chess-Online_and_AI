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

bool boardbox::checkAttackedByKnight(int side, int x, int y)
{
    Piece isKnight = getboard()->getbox(x+1,y+2)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x+1,y-2)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x-1,y+2)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x-1,y-2)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x+2,y+1)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x+2,y-1)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x-2,y+1)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    isKnight = getboard()->getbox(x-2,y-1)->getpiece();
    if (isKnight && isKnight->getType() == 6 && isKnight->getside() != side)
        return true;
    return false;
}

bool boardbox::checkAttackedByQueen(int side, int x, int y)
{
    int i = x, j = y;
    Piece isQueen; // copy from rooks function
    for (;i<=7 && j <= 7;i++)
    {
        isQueen = getboard()->getbox(i,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
        j++;
    }
    i = x, j = y;
    for (;i<=7 && j >= 0;i++)
    {
        isQueen = getboard()->getbox(i,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
        j--;
    }
    i = x, j = y;
    for (;i>=0 && j <= 7;i--)
    {
        isQueen = getboard()->getbox(i,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
        j++;
    }
    i = x, j = y;
    for (;i>=0 && j >= 0;i--)
    {
        isQueen = getboard()->getbox(i,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
        j--;
    }
    int i = x, j = y;
    for (;i<=7;i++)
    {
        isQueen = getboard()->getbox(i,y)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
    }
    i = x;
    for (;i>=0;i--)
    {
        isQueen = getboard()->getbox(i,y)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
    }
    i = x, j = y;
    for (;j>=0;i--)
    {
        isQueen = getboard()->getbox(x,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
    }
    j = y;
    for (;j<=7; j++)
    {
        isQueen = getboard()->getbox(x,j)->getpiece();
        if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
            break;
        if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
            return true;
    }
    return false;
}

bool boardbox::checkAttackedByBishop(int side, int x, int y)
{
    int i = x, j = y;
    Piece isBishop;
    for (;i<=7 && j <= 7;i++)
    {
        isBishop = getboard()->getbox(i,j)->getpiece();
        if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
            break;
        if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
            return true;
        j++;
    }
    i = x, j = y;
    for (;i<=7 && j >= 0;i++)
    {
        isBishop = getboard()->getbox(i,j)->getpiece();
        if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
            break;
        if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
            return true;
        j--;
    }
    i = x, j = y;
    for (;i>=0 && j <= 7;i--)
    {
        isBishop = getboard()->getbox(i,j)->getpiece();
        if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
            break;
        if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
            return true;
        j++;
    }
    i = x, j = y;
    for (;i>=0 && j >= 0;i--)
    {
        isBishop = getboard()->getbox(i,j)->getpiece();
        if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
            break;
        if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
            return true;
        j--;
    }
    return false;
}

bool boardbox::checkAttackedByPawn(int side, int x, int y)
{
    int pace = -1 + side *2;
    Piece isPawn = getboard()->getbox(x+1,y+pace)->getpiece();
    if (isPawn->getType() == 4 && isPawn->getside() != side)
        return true;
    isPawn = getboard()->getbox(x-1,y+pace)->getpiece();
    if (isPawn->getType() == 4 && isPawn->getside() != side)
        return true;
    return false;
}

bool boardbox::checkAttackedByRook(int side, int x, int y)
{
    int i = x, j = y;
    Piece isRook;
    for (;i<=7;i++)
    {
        isRook = getboard()->getbox(i,y)->getpiece();
        if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
            break;
        if (isRook && isRook->getType() == 7 && isRook->getside() != side)
            return true;
    }
    i = x;
    for (;i>=0;i--)
    {
        isRook = getboard()->getbox(i,y)->getpiece();
        if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
            break;
        if (isRook && isRook->getType() == 7 && isRook->getside() != side)
            return true;
    }
    i = x, j = y;
    for (;j>=0;i--)
    {
        isRook = getboard()->getbox(x,j)->getpiece();
        if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
            break;
        if (isRook && isRook->getType() == 7 && isRook->getside() != side)
            return true;
    }
    j = y;
    for (;j<=7; j++)
    {
        isRook = getboard()->getbox(x,j)->getpiece();
        if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
            break;
        if (isRook && isRook->getType() == 7 && isRook->getside() != side)
            return true;
    }
    return false;
}

bool boardbox::checkAttackedByKing(int side, int x, int y)
{
    Piece isKing;
    if (x > 0)
    {
        int i = x - 1;
        for (int k =-1; k<2;k++)
        {
            isKing = getboard()->getbox(i,y+k)->getpiece();
            if (isKing && isKing->getType() == 9 && isKing->getside() != side)
                return true;
        }
    }
    if (x < 7)
    {
        int i = x - 1;
        for (int k =-1; k<2;k++)
        {
            isKing = getboard()->getbox(i,y+k)->getpiece();
            if (isKing && isKing->getType() == 9 && isKing->getside() != side)
                return true;
        }
    }
    isKing = getboard()->getbox(x,y-1)->getpiece();
    if (isKing && isKing->getType() == 9 && isKing->getside() != side)
        return true;
    isKing = getboard()->getbox(x,y+1)->getpiece();
    if (isKing && isKing->getType() == 9 && isKing->getside() != side)
        return true;
    return false;
}

bool boardbox::checkAttacked(int side, int x, int y)
{
    return (checkAttackedByBishop(side, x, y) || checkAttackedByKing(side, x, y) || checkAttackedByKnight(side, x, y) || checkAttackedByPawn(side, x, y) ||checkAttackedByQueen(side, x, y) || checkAttackedByRook(side ,x, y));
}
