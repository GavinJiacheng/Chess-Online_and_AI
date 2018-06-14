#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "gameitems/gameboard.h"
#include "gameitems/boardbox.h"


class game:public QGraphicsView
{
    Q_OBJECT
public:
    game(QWidget *parent = NULL);
    //~game();
    void placeTheBoard();
    void addToScene(QGraphicsItem *item);
    boardbox* getbox(int i, int j);
    void pickUpPieces(Piece* P);
    void placePieces();
    void mainmenu();

    void mouseMoveEvent(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    int getTurn();
    void setTurn(int i);
    void changeTurn();
    void playOffline();
    void SetGamecolor();

public slots:
    void start();


private:
    QGraphicsScene* gameScene;
    gameboard *board;
    QPointF originalPos;
    Piece* piece_to_placed;
    int turn; // 1 =black, 0 = white
    QGraphicsTextItem * turnDisplay;
};

#endif // GAME_H
