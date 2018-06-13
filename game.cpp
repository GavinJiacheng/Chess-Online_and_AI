#include "game.h"
#include "gameitems/gameboard.h"
#include <QColor>
#include <QDebug>
#include <math.h>

int Piece::deadBlack = 0;
int Piece::deadWhite = 0;

game::game(QWidget *parent):QGraphicsView(parent)
{
    //Making the Scene
    board = NULL;
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);

    //Making the view
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor gray(Qt::gray);
    brush.setColor(gray);
    setBackgroundBrush(brush);
    piece_to_placed = NULL; // LOL , you must declare this fucking piece of shit.

    turn = 0; //0 is white and 1 is black
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");


}

void game::placeTheBoard()
{
    board = new gameboard();
    board->placeBoxes();
}


void game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void game::start()
{
    addToScene(turnDisplay);
    placeTheBoard();
    placePieces();
}

boardbox *game::getbox(int i, int j)
{
    boardbox *ret = NULL;
    if (board != NULL)
        ret= board->getbox(i,j);
    if (ret)
        return ret;
    else
        return NULL;
}

void game::pickUpPieces(Piece *P)
{
    if (/*card->getOwner() == getWhosTurn() &&*/ P != NULL)
    {
        piece_to_placed = P;
        originalPos = P->pos();
    }
}

void game::placePieces()
{
    if (board != NULL)
        board->startup();
}

void game::mouseMoveEvent(QMouseEvent *event)
{
    if (piece_to_placed){
       piece_to_placed->setPos((event->pos().x()-50),(event->pos().y()-50));
    }
    QGraphicsView::mouseMoveEvent(event);
}

void game::mouseReleaseEvent(QMouseEvent *event)
{
    int startX = event->pos().x();
    int startY = event->pos().y();
    QGraphicsView::mouseReleaseEvent(event);
    int finalX = startX/100*100;
    int finalY = (startY-50)/100*100;
    int x = finalX/100-3;
    int y = finalY/100;
    finalY += 50;

    //if (piece_to_placed && piece_to_placed->canmove(finalPos.x(),finalPos.y())){
   //     piece_to_placed->setPos(finalPos);
    //    piece_to_placed = NULL;
    // } // fuck you, if this function doest run, the piece is still not null, fuck it.

    if (piece_to_placed)
    {
        if (startX < 300 || startX >= 1100)
        {
            piece_to_placed->setPos(originalPos);
            piece_to_placed = NULL;
            return;
        }
        else if (startY < 50 ||startY >= 850)
        {
            piece_to_placed->setPos(originalPos);
            piece_to_placed = NULL;
            return;
        }
        boardbox *targetBox = getbox(x,y);
        if(piece_to_placed->pawnAttack(x,y) && targetBox->hasPiece() && targetBox->getpiece()->getside() != piece_to_placed->getside())
        {
            targetBox->getpiece()->die();
            piece_to_placed->setPos(finalX,finalY);
            piece_to_placed->setlocation(x,y);
            piece_to_placed->moved();
            piece_to_placed->getCurrentBox()->removepiece();
            piece_to_placed->setCurrentBox(targetBox);
            piece_to_placed->getCurrentBox()->placepiece(piece_to_placed);
            changeTurn();
            piece_to_placed = NULL;
            return;
        }
        else if(piece_to_placed->canmove(x,y))
        {
            if (targetBox->hasPiece())
            {
                if (targetBox->getpiece()->getside() == piece_to_placed->getside())
                {
                    piece_to_placed->setPos(originalPos);
                    piece_to_placed = NULL;
                    return;
                }
                else
                    targetBox->getpiece()->die();
            }
            piece_to_placed->setPos(finalX,finalY);
            piece_to_placed->setlocation(x,y);
            piece_to_placed->moved();
            piece_to_placed->getCurrentBox()->removepiece();
            piece_to_placed->setCurrentBox(targetBox);
            piece_to_placed->getCurrentBox()->placepiece(piece_to_placed);
            changeTurn();
            piece_to_placed = NULL;
            return;
            //What the fuck are you ? QGraphicsView::mouseReleaseEvent(event);
        }
        else
        {
            piece_to_placed->setPos(originalPos);
            //qDebug() << "o:" <<piece_to_placed->location[0] << ","<<piece_to_placed->location[1];
            //qDebug() << "f:" <<finalX/100-3 << ","<<(finalY-50)/100;
            //qDebug() << "f2:" <<x << ","<<y;
            piece_to_placed = NULL;
            return;
        }
     }
    piece_to_placed = NULL;
}

int game::getTurn()
{
    return turn;
}

void game::setTurn(int i)
{
    turn = i;
}

void game::changeTurn()
{
    if(turn)
    {
        turn = 0;
        turnDisplay->setPlainText("Turn : WHITE");
    }
    else
    {
        turn = 1;
        turnDisplay->setPlainText("Turn : BLACK");
    }
}
