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
    if (getboard()->getbox(x+1,y+2) && getboard()->getbox(x+1,y+2)->getpiece() && getboard()->getbox(x+1,y+2)->getpiece()->getType() == 6 && getboard()->getbox(x+1,y+2)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x+1,y-2) && getboard()->getbox(x+1,y-2)->getpiece() && getboard()->getbox(x+1,y-2)->getpiece()->getType() == 6 && getboard()->getbox(x+1,y-2)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x-1,y+2) && getboard()->getbox(x-1,y+2)->getpiece() && getboard()->getbox(x-1,y+2)->getpiece()->getType() == 6 && getboard()->getbox(x-1,y+2)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x-1,y-2) && getboard()->getbox(x-1,y-2)->getpiece() && getboard()->getbox(x-1,y-2)->getpiece()->getType() == 6 && getboard()->getbox(x-1,y-2)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x+2,y+1) && getboard()->getbox(x+2,y+1)->getpiece() && getboard()->getbox(x+2,y+1)->getpiece()->getType() == 6 && getboard()->getbox(x+2,y+1)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x+2,y-1) && getboard()->getbox(x+2,y-1)->getpiece() && getboard()->getbox(x+2,y-1)->getpiece()->getType() == 6 && getboard()->getbox(x+2,y-1)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x-2,y+1) && getboard()->getbox(x-2,y+1)->getpiece() && getboard()->getbox(x-2,y+1)->getpiece()->getType() == 6 && getboard()->getbox(x-2,y+1)->getpiece()->getside() != side)
        return true;
    if (getboard()->getbox(x-2,y-1) && getboard()->getbox(x-2,y-1)->getpiece() && getboard()->getbox(x-2,y-1)->getpiece()->getType() == 6 && getboard()->getbox(x-2,y-1)->getpiece()->getside() != side)
        return true;
    return false;
}

bool boardbox::checkAttackedByQueen(int side, int x, int y)
{
    int i = x, j = y;
    Piece *isQueen; // copy from rooks function
    i++;
    j++;
    for (;i<=7 && j <= 7;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
        j++;
    }
    i = x, j = y;
    i++;
    j--;
    for (;i<=7 && j >= 0;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
        j--;
    }
    i = x, j = y;
    i--;
    j++;
    for (;i>=0 && j <= 7;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
        j++;
    }
    i = x, j = y;
    i--;
    j--;
    for (;i>=0 && j >= 0;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
        j--;
    }
    i = x, j = y;
    i++;
    for (;i<=7;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,y)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
    }
    i = x;
    i--;
    for (;i>=0;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(i,y)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
    }
    i = x, j = y;
    j--;
    for (;j>=0;j--)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(x,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
    }
    j = y;
    j++;
    for (;j<=7; j++)
    {
        if (getboard()->getbox(i,j))
        {
            isQueen = getboard()->getbox(x,j)->getpiece();
            if (isQueen && (isQueen->getType() != 8 || isQueen->getside() == side))
                break;
            if (isQueen && isQueen->getType() == 8 && isQueen->getside() != side)
                return true;
        }
    }
    return false;
}

bool boardbox::checkAttackedByBishop(int side, int x, int y)
{
    int i = x, j = y;
    Piece *isBishop;
    i++;
    j++;
    for (;i<=7 && j <= 7;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isBishop = getboard()->getbox(i,j)->getpiece();
            if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
                break;
            if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
                return true;
        }
        j++;
    }
    i = x, j = y;
    i++;
    j--;
    for (;i<=7 && j >= 0;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isBishop = getboard()->getbox(i,j)->getpiece();
            if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
                break;
            if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
                return true;
        }
        j--;
    }
    i = x, j = y;
    i--;
    j++;
    for (;i>=0 && j <= 7;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isBishop = getboard()->getbox(i,j)->getpiece();
            if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
                break;
            if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
                return true;
        }
        j++;
    }
    i = x, j = y;
    i--;
    j--;
    for (;i>=0 && j >= 0;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isBishop = getboard()->getbox(i,j)->getpiece();
            if (isBishop && (isBishop->getType() != 5 || isBishop->getside() == side))
                break;
            if (isBishop && isBishop->getType() == 5 && isBishop->getside() != side)
                return true;
        }
        j--;
    }
    return false;
}

bool boardbox::checkAttackedByPawn(int side, int x, int y)
{
    int pace = -1 + side *2;
    Piece *isPawn;
    if (getboard()->getbox(x+1,y+pace))
    {
        isPawn = getboard()->getbox(x+1,y+pace)->getpiece();
        if (isPawn && isPawn->getType() == 4 && isPawn->getside() != side)
            return true;
    }
    if (getboard()->getbox(x-1,y+pace))
    {
        isPawn = getboard()->getbox(x-1,y+pace)->getpiece();
        if (isPawn && isPawn->getType() == 4 && isPawn->getside() != side)
            return true;
    }
    return false;
}

bool boardbox::checkAttackedByRook(int side, int x, int y)
{
    int i = x, j = y;
    Piece *isRook;
    i++;
    for (;i<=7;i++)
    {
        if (getboard()->getbox(i,j))
        {
            isRook = getboard()->getbox(i,y)->getpiece();
            if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
                break;
            if (isRook && isRook->getType() == 7 && isRook->getside() != side)
                return true;
        }
    }
    i = x;
    i--;
    for (;i>=0;i--)
    {
        if (getboard()->getbox(i,j))
        {
            isRook = getboard()->getbox(i,y)->getpiece();
            if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
                break;
            if (isRook && isRook->getType() == 7 && isRook->getside() != side)
                return true;
        }
    }
    i = x, j = y;
    j--;
    for (;j>=0;j--)
    {
        if (getboard()->getbox(i,j))
        {
            isRook = getboard()->getbox(x,j)->getpiece();
            if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
                break;
            if (isRook && isRook->getType() == 7 && isRook->getside() != side)
                return true;
        }
    }
    j = y;
    j++;
    for (;j<=7; j++)
    {
        if (getboard()->getbox(i,j))
        {
            isRook = getboard()->getbox(x,j)->getpiece();
            if (isRook && (isRook->getType() != 7 || isRook->getside() == side))
                break;
            if (isRook && isRook->getType() == 7 && isRook->getside() != side)
                return true;
        }
    }
    return false;
}

bool boardbox::checkAttackedByKing(int side, int x, int y)
{
    Piece *isKing;
    if (x > 0)
    {
        int i = x - 1;
        for (int k =-1; k<2;k++)
        {
            if (getboard()->getbox(i,y+k))
            {
                isKing = getboard()->getbox(i,y+k)->getpiece();
                if (isKing && isKing->getType() == 9 && isKing->getside() != side)
                    return true;
            }
        }
    }
    if (x < 7)
    {
        int i = x - 1;
        for (int k =-1; k<2;k++)
        {
            if (getboard()->getbox(i,y+k))
            {
                isKing = getboard()->getbox(i,y+k)->getpiece();
                if (isKing && isKing->getType() == 9 && isKing->getside() != side)
                    return true;
            }
        }
    }
    if (getboard()->getbox(x,y-1))
    {
        isKing = getboard()->getbox(x,y-1)->getpiece();
        if (isKing && isKing->getType() == 9 && isKing->getside() != side)
            return true;
    }
    if (getboard()->getbox(x,y+1))
    {
        isKing = getboard()->getbox(x,y+1)->getpiece();
        if (isKing && isKing->getType() == 9 && isKing->getside() != side)
            return true;
    }
    return false;
}

bool boardbox::checkAttacked(int side)
{
    int x = col;
    int y = row;
    return (checkAttackedByBishop(side, x, y) || checkAttackedByKing(side, x, y) || checkAttackedByKnight(side, x, y) || checkAttackedByPawn(side, x, y) ||checkAttackedByQueen(side, x, y) || checkAttackedByRook(side ,x, y));
}

int boardbox::getCol()
{
    return col;
}

int boardbox::getRow()
{
    return row;
}
