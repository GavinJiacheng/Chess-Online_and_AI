#ifndef PIECE_H
#define PIECE_H
class boardbox;
#include "boardbox.h"
#include <QMouseEvent>
#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>


class Piece:public QGraphicsPixmapItem
{
public:
    static int deadBlack;
    static int deadWhite;
    Piece(int color, int col, int row, QGraphicsItem *parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(boardbox *Box);
    boardbox *getCurrentBox();
    virtual int die(); //return -1 if this piece is not king.
    void setWeight(int w);
    void setdie(bool);
    int getWeight();
    virtual void setImage() =0;
    int getside();
    virtual bool canmove(int x, int y) = 0;
    void setlocation(int x, int y);
    int getCol();
    int getRow();
    void moved();
    bool Ismoved();
    bool dead();
    virtual int getType() = 0; // 9 king, 8 queen, 7 rook, 6 knight, 5 bishop, 4 pawn
    virtual bool pawnAttack(int x, int y);
    void moveTo(int x, int y);
    void tryToMoveTo(int x, int y);
    void Reset_DeadPieces();
    int origin_zValue = 0;

    //int debug;

protected:
    int location[2];
    int side; //1 = black, 0 = white
    boardbox *CurrentBox;

private:
    bool isdead = false;
    int weight;
    bool ismoved = false;

};


#endif // PIECE_H
