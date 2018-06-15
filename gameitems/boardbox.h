#ifndef BOARDBOX_H
#define BOARDBOX_H
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>

class Piece;
#include "piece.h"
class gameboard;
#include "gameboard.h"

class boardbox:public QGraphicsRectItem
{
public:
     boardbox(int col,int row,QGraphicsItem *parent = NULL);
    //void setcolor(QColor Color);
    void resetcolor();
   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void placepiece(Piece *newPiece);
    void removepiece();
    bool hasPiece();
    void setboard(gameboard* board);
    gameboard *getboard();
    Piece *getpiece();
    bool checkAttackedByKnight(int side, int x, int y);
    bool checkAttackedByQueen(int side, int x, int y);
    bool checkAttackedByBishop(int side, int x, int y);
    bool checkAttackedByPawn(int side, int x, int y);
    bool checkAttackedByRook(int side, int x, int y);
    bool checkAttackedByKing(int side, int x, int y);
    bool checkAttacked(int side);
    int getCol();
    int getRow();
    //bool IsThisBox();
private:
    gameboard *board;
    QColor color;
    int col;
    int row;
    QBrush brush;
    Piece * currentPiece;
};

#endif // BOARDBOX_H
