#ifndef CHESSROOM_H
#define CHESSROOM_H

#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
class gameHall;
#include "gamehall.h"

class ChessRoom:public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ChessRoom(gameHall* hall, QString Name, int ID, bool isplay, QGraphicsItem* parent=NULL);
    //~ChessRoom();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked(int);

private:
    QString name;
    int ID;
    bool isPlaying;
    gameHall* gamehall;
    void setWaitingImage();
    void setPlayingImage();
    QGraphicsTextItem* HostsName;
};



#endif // CHESSROOM_H


