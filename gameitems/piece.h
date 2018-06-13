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
    void die();
    void setWeight(int w);
    int getWeight();
    virtual void setImage() =0;
    int getside();
    virtual bool canmove(int x, int y) = 0;
    void setlocation(int x, int y);
    void moved();
    bool Ismoved();
    bool dead();
        int location[2];

    //int debug;

protected:
    //int location[2];
    int side; //1 = black, 0 = white

private:
    bool isdead = false;
    boardbox *CurrentBox;
    int weight;
    bool ismoved = false;

};


#endif // PIECE_H
