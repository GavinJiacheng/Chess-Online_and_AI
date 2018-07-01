#ifndef CHESSROOM_H
#define CHESSROOM_H

#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
class gameLobby;
#include "gamelobby.h"

class ChessRoom:public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ChessRoom(gameLobby* lobby, QString Name, int ID, bool isplay, QGraphicsItem* parent=NULL);
    void player2(QString player2name);
    //~ChessRoom();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked(int);

private:
    QString name;
    QString p2name = "";
    int ID;
    bool isPlaying;
    gameLobby* Lobby;
    void setWaitingImage();
    void setPlayingImage();
    QGraphicsTextItem* HostsName;
    QGraphicsTextItem* P2Name = NULL;
};



#endif // CHESSROOM_H


