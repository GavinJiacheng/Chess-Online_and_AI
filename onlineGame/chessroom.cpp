#include "chessroom.h"


ChessRoom::ChessRoom(gameHall *hall, QString Name, int ID, bool isplay, QGraphicsItem *parent)
{
    this->gamehall = hall;
    this->name = Name;
    this->ID = ID;
    this->isPlaying = isplay;
    if (isPlaying)
    {
        setPlayingImage();
    }
    else
    {
        setWaitingImage();
    }
    HostsName = new QGraphicsTextItem(name,this); // button is the parent of this text
    int xPos = 200 - HostsName->boundingRect().width()/2;
    int yPos = 160;
    HostsName->setPos(xPos,yPos);
    qDebug() << "ID is: " <<ID<<" name is: "<<Name;
}

void ChessRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isPlaying)
       emit clicked(this->ID);
}


void ChessRoom::setWaitingImage()
{
    setPixmap(QPixmap(":/online/images/Waiting.png"));
}

void ChessRoom::setPlayingImage()
{
    setPixmap(QPixmap(":/online/images/Playing.png"));
}
