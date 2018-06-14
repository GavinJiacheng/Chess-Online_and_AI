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
                qDebug() << "fuck";
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
    return (WKingbox->checkAttacked() || BKingbox->checkAttacked());
}

