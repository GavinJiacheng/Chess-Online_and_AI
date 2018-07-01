#include "chessroom.h"


ChessRoom::ChessRoom(gameLobby *Lobby, QString Name, int ID, bool isplay, QGraphicsItem *parent)
{
    this->Lobby = Lobby;
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

void ChessRoom::player2(QString player2name)
{
    if  (isPlaying)
    {
        this->p2name = player2name;
        P2Name = new QGraphicsTextItem(p2name,this); // button is the parent of this text
        int xPos = 15;
        int yPos = 160;
        P2Name->setPos(xPos,yPos);
    }
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
