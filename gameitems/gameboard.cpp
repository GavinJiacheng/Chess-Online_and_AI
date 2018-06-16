#include <QDebug>
#include "gameboard.h"
#include "boardbox.h"
#include "game.h"
#include "gameboard.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"

extern game* Game;
gameboard::gameboard()
{
    Checking = false;
    OldPiece = NULL;
    supposedDiedPiece = NULL;
}

gameboard::~gameboard()
{
    for(int i =0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            delete boxes[i][j];
            boxes[i][j] = NULL;
        }
    }
    qDeleteAll(black);
    black.clear();
    qDeleteAll(white);
    white.clear();
}

void gameboard::placeBoxes()
{
    for(int i =0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            boardbox* boxes = new boardbox(i,j);
            boxes->setPos(300+i*100,50+j*100);
            boxes->resetcolor();
            this->boxes[i][j] = boxes;
            boxes->setboard(this);
            if (boxes == NULL)
                qDebug() << "fuck placeBoxes!";
            else
                Game->addToScene(boxes);
        }
    }
}

boardbox *gameboard::getbox(int i, int j)
{
    if (i <0 || i>7 ||j<0||j>7)
        return NULL;
    else
        return boxes[i][j];
}

void gameboard::startup()
{
    qDeleteAll(black);
    black.clear();
    qDeleteAll(white);
    white.clear();
    OldPiece = NULL;
    supposedDiedPiece = NULL;
    Piece *piece;
    //black pieces
    piece = new rook(1,0,0);
    piece->setPos(300,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new knight(1,1,0);
    piece->setPos(400,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new bishop(1,2,0);
    piece->setPos(500,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new queen(1,3,0);
    piece->setPos(600,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new king(1,4,0);
    piece->setPos(700,50);
    BKing = piece;
    Game->addToScene(piece);
    black.append(piece);
    piece = new bishop(1,5,0);
    piece->setPos(800,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new knight(1,6,0);
    piece->setPos(900,50);
    Game->addToScene(piece);
    black.append(piece);
    piece = new rook(1,7,0);
    piece->setPos(1000,50);
    Game->addToScene(piece);
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new pawn(1,i,1);
        piece->setPos(300+i*100,150);
        Game->addToScene(piece);
        black.append(piece);
    }
    // white pieces
    for(int i = 0; i < 8; i++) {
        piece = new pawn(0,i,6);
        piece->setPos(300+i*100,650);
        Game->addToScene(piece);
        white.append(piece);
    }
    piece = new rook(0,0,7);
    piece->setPos(300,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new knight(0,1,7);
    piece->setPos(400,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new bishop(0,2,7);
    piece->setPos(500,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new queen(0,3,7);
    piece->setPos(600,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new king(0,4,7);
    piece->setPos(700,750);
    WKing = piece;
    Game->addToScene(piece);
    white.append(piece);
    piece = new bishop(0,5,7);
    piece->setPos(800,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new knight(0,6,7);
    piece->setPos(900,750);
    Game->addToScene(piece);
    white.append(piece);
    piece = new rook(0,7,7);
    piece->setPos(1000,750);
    Game->addToScene(piece);
    white.append(piece);
}

bool gameboard::checkCanCheck()
{
    boardbox *WKingbox = WKing->getCurrentBox();
    boardbox *BKingbox = BKing->getCurrentBox();
    Checking =(WKingbox->checkAttacked(0) || BKingbox->checkAttacked(1));
    return (Checking);
}

int gameboard::playerSside()
{
    return playerside;
}

void gameboard::appendPieces(Piece* P)
{
    if(P->getside())
        black.append(P);
    else
        white.append(P);
}

void gameboard::findPossibleMove(int side)
{
    qDeleteAll(possible_boxNpiece_Black);
    possible_boxNpiece_Black.clear();
    qDeleteAll(possible_boxNpiece_White);
    possible_boxNpiece_White.clear();
    int** map = createloaclmap();
    findallmovess *thing = new findallmovess(side, map);
    addtoboxes(thing);
    delete thing;
}

void gameboard::addtoboxes(findallmovess *thing)
{
    for (moves* visitor : thing->allmoves)
    {
        int FX = visitor->fromX;
        int FY = visitor->fromY;
        int TX = visitor->ToX;
        int TY = visitor->ToY;
        Piece* P = getbox(FX,FY)->getpiece();
        addPossibleBox(P,TX,TY);
    }
}

/*
void gameboard::findPossibleMove(int side)
{
    qDeleteAll(possible_boxNpiece_Black);
    possible_boxNpiece_Black.clear();
    qDeleteAll(possible_boxNpiece_White);
    possible_boxNpiece_White.clear();
    if (side)
    {
        int length = black.length();
        for (int i = 0; i<length; i++) {
            if (!black[i]->dead())
                checkPossiblemove(black[i]);
        }
    }
    else
    {
        int length = white.length();
        for (int i = 0; i<length; i++) {
            if (!white[i]->dead())
                checkPossiblemove(white[i]);
        }
    }
} */

void gameboard::checkPossiblemove(Piece *P)
{
    if (P == NULL)
        qDebug() << "Bugs here.";
    if (P->getType() == 9)
        checkKingsMove(P);
    else if (P->getType() == 8)
        checkQueensMove(P);
    else if (P->getType() == 7)
        checkRooksMove(P);
    else if (P->getType() == 6)
        checkKnightsMove(P);
    else if (P->getType() == 5)
        checkBishopsMove(P);
    else if (P->getType() == 4)
        checkPawnsMove(P);
    else //??? It shouldn't be this branch!
        qDebug() << "FUCK BUGS";
}

void gameboard::checkKingsMove(Piece *P)
{
    int x = P->getCol() -1;
    int y = P->getRow() +1;
    for(;y>P->getRow()-2;y--)
    {
        if (getbox(x,y) && P->canmove(x,y))
        {
            boardbox *box = getbox(x,y);
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
        }
    }
    x = P->getCol() +1;
    y = P->getRow() +1;
    for(;y>P->getRow()-2;y--)
    {
        if (getbox(x,y) && P->canmove(x,y) )
        {
            boardbox *box = getbox(x,y);
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
        }
    }
    x = P->getCol();
    y = P->getRow() +1;
    if (getbox(x,y) && P->canmove(x,y))
    {
        boardbox *box = getbox(x,y);
        if (!box->hasPiece())
            addPossibleBox(P,x,y);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x,y);
    }
    y = P->getRow() -1;
    if (getbox(x,y) && P->canmove(x,y))
    {
        boardbox *box = getbox(x,y);
        if (!box->hasPiece())
            addPossibleBox(P,x,y);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x,y);
    }

     //Sorry, no castling!
}

void gameboard::checkQueensMove(Piece *P)
{
    int x = P->getCol();
    int y = P->getRow();
    x++;
    y++;
    for(; x <=7 && y <=7; x++)
    {
        if (P->canmove(x,y))
        {
            boardbox *box = getbox(x,y);
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y++;
    }
    x = P->getCol();
    y = P->getRow();
    x++;
    y--;
    boardbox *box;
    for(; x <=7 && y >=0; x++)
    {
        box = getbox(x,y);
        if (P->canmove(x,y))
        {
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y--;
    }
    x = P->getCol();
    y = P->getRow();
    x--;
    y--;
    for(; x >=0 && y >=0; x--)
    {
        box = getbox(x,y);
        if (P->canmove(x,y))
        {
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y--;
    }
    x = P->getCol();
    y = P->getRow();
    x--;
    y++;
    for(; x >=0 && y <=7; x--)
    {
        box = getbox(x,y);
        if (P->canmove(x,y))
        {
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y++;
    }
    // do rooks move
    x = P->getCol();
    y = P->getRow();
    x--;
    for(; x >=0; x--)
    {
        box = getbox(x,y);
        if (P->canmove(x,y))
        {
            if (!box->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(box->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    x = P->getCol();
    x++;
    for(; x <=7; x++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    x = P->getCol();
    y++;
    for(; y <=7; y++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    y = P->getRow();
    y--;
    for(; y >=0; y--)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
}

void gameboard::checkRooksMove(Piece *P)
{
    int x = P->getCol();
    int y = P->getRow();
    x--;
    for(; x >=0; x--)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    x = P->getCol();
    x++;
    for(; x <=7; x++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    x = P->getCol();
    y++;
    for(; y <=7; y++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
    y = P->getRow();
    y--;
    for(; y >=0; y--)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
    }
}

void gameboard::checkKnightsMove(Piece *P)
{
    int x = P->getCol();
    int y = P->getRow();
    boardbox *box = getbox(x+1,y+2);
    if (box && P->canmove(x+1,y+2))
    {
        if (!box->hasPiece())
             addPossibleBox(P,x+1,y+2);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x+1,y+2);
    }
    box = getbox(x+1,y-2);
    if (box && P->canmove(x+1,y-2))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x+1,y-2);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x+1,y-2);
    }
    box = getbox(x-1,y+2);
    if (getbox(x-1,y+2) && P->canmove(x-1,y+2))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x-1,y+2);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x-1,y+2);
    }
    box = getbox(x-1,y-2);
    if (getbox(x-1,y-2) && P->canmove(x-1,y-2))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x-1,y-2);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x-1,y-2);
    }
    box = getbox(x+2,y+1);
    if (getbox(x+2,y+1) && P->canmove(x+2,y+1))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x+2,y+1);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x+2,y+1);
    }
    box = getbox(x+2,y-1);
    if (getbox(x+2,y-1) && P->canmove(x+2,y-1))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x+2,y-1);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x+2,y-1);
    }
    box = getbox(x-2,y+1);
    if (getbox(x-2,y+1) && P->canmove(x-2,y+1))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x-2,y+1);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x-2,y+1);
    }
    box = getbox(x-2,y-1);
    if (box && P->canmove(x-2,y-1))
    {
        if (!box->hasPiece())
            addPossibleBox(P,x-2,y-1);
        else
            if(box->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x-2,y-1);
    }
}

void gameboard::checkBishopsMove(Piece *P)
{
    int x = P->getCol();
    int y = P->getRow();
    x++;
    y++;
    for(; x <=7 && y <=7; x++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y++;
    }
    x = P->getCol();
    y = P->getRow();
    x++;
    y--;
    for(; x <=7 && y >=0; x++)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y--;
    }
    x = P->getCol();
    y = P->getRow();
    x--;
    y--;
    for(; x >=0 && y >=0; x--)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y--;
    }
    x = P->getCol();
    y = P->getRow();
    x--;
    y++;
    for(; x >=0 && y <=7; x--)
    {
        if (P->canmove(x,y))
        {
            if (!getbox(x,y)->hasPiece())
                addPossibleBox(P,x,y);
            else
            {
                if(getbox(x,y)->getpiece()->getside()!=P->getside())
                    addPossibleBox(P,x,y);
                else
                    break;
            }
        }
        else
            break;
        y++;
    }
}

void gameboard::checkPawnsMove(Piece *P)
{
    int x = P->getCol();
    int y = P->getRow();
    int pace = -1 + 2* P->getside();
    if (getbox(x,y+pace) && P->canmove(x,y+pace))
    {
        addPossibleBox(P,x,y+pace);
        if (getbox(x,y+pace+pace) && P->canmove(x,y+pace+pace))
            addPossibleBox(P,x,y+pace+pace);
    }
    if (getbox(x+1,y+pace) && P->pawnAttack(x+1,y+pace))
    {
        if (getbox(x+1,y+pace)->hasPiece())
            if(getbox(x+1,y+pace)->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x+1,y+pace);
    }
    if (getbox(x-1,y+pace) && P->pawnAttack(x-1,y+pace))
    {
        if (getbox(x-1,y+pace)->hasPiece())
            if(getbox(x-1,y+pace)->getpiece()->getside()!=P->getside())
                addPossibleBox(P,x-1,y+pace);
    }
}

void gameboard::addPossibleBox(Piece *P,int x,int y)
{
    possible_boxNpiece *NewPos = new possible_boxNpiece(P, getbox(x,y));
    if (P->getside())
        possible_boxNpiece_Black.append(NewPos);
    else
        possible_boxNpiece_White.append(NewPos);
}

void gameboard::supposeddie(Piece *P)
{
    supposedDiedPiece = P;
}

void gameboard::triedPiece(Piece *P)
{
    OldPiece = P;
}


void gameboard::gobackThinking()
{
    if(!OldPiece)
        return;
    boardbox *oldtargetBox = getbox(oldlocation[0],oldlocation[1]);
    boardbox *targetBox = getbox(OldPiece->getCol(),OldPiece->getRow());
    OldPiece->setlocation(oldlocation[0],oldlocation[1]);
    targetBox->removepiece();
    OldPiece->setCurrentBox(oldtargetBox);
    oldtargetBox->placepiece(OldPiece);
    OldPiece = NULL;
    if(supposedDiedPiece)
    {
        supposedDiedPiece->setdie(false);
        targetBox->placepiece(supposedDiedPiece);
        supposedDiedPiece = NULL;
    }
}

void gameboard::NosupposedDie()
{
    supposedDiedPiece = NULL;
}

int **gameboard::getlocalmap()
{
    return loaclmap;
}

int **gameboard::createloaclmap()
{
    delete loaclmap;
    int **new_board=new int *[8];
    for(int i=0; i<8; ++i)
    {
        new_board[i] = new int[8];
        for(int j=0; j<8; ++j)
        {
            new_board[i][j] = 0;
        }
    }
    for (Piece* targetP:black)
    {
        if (!targetP->dead())
        {
            int Px = targetP->getCol();
            int Py = targetP->getRow();
            int type = -targetP->getType();
            new_board[Px][Py] = type;
        }
    }
    for (Piece* targetP:white)
    {
        if (!targetP->dead())
        {
            int Px = targetP->getCol();
            int Py = targetP->getRow();
            int type = targetP->getType();
            new_board[Px][Py] = type;
        }
    }
    loaclmap = new_board;
    return new_board;
}

