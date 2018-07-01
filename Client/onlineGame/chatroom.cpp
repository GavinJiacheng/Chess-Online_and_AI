#include "chatroom.h"

#include <QDebug>
#include <string>

#pragma execution_character_set("utf-8")

Chatroom::Chatroom(gameLobby *parent,Qt::WindowFlags f): QDialog(parent,f)
{
    Parent = parent;
    setWindowTitle(tr("TCP Client"));

    contentListWidget = new QListWidget;

    sendLineEdit = new QLineEdit;

    userNameLabel = new QLabel(tr("Your Name:"));
    userNameLineEdit = new QLineEdit;

    sendBtn= new QPushButton(tr("Send"));
    CreateChessRoomBtn = new QPushButton(tr("Create a Game Room"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(userNameLabel,1,0);
    mainLayout->addWidget(userNameLineEdit,1,1);
    mainLayout->addWidget(sendLineEdit,2,0,1,2);
    mainLayout->addWidget(sendBtn,3,0,1,2);
    mainLayout->addWidget(CreateChessRoomBtn,4,0,1,2);
    userNameLineEdit->setText("Smart_Gavin");
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(CreateChessRoomBtn,SIGNAL(clicked()),this,SLOT(CreateRoom()));
}

void Chatroom::Showmessage(char* String)
{
    QString msg= QString(QLatin1String(String));
    //qDebug()<< msg;
    contentListWidget->addItem(msg);
}


void Chatroom::sendMessage()
{
    if(sendLineEdit->text()=="")
        return ;
    QString msg= userNameLineEdit->text()+":"+sendLineEdit->text();
    //qDebug()<< msg;
    if (msg.length() <= 256)
    {
        std::string user = userNameLineEdit->text().toStdString();
        std::string mess = msg.toStdString();
        //qDebug()<< mess;
        bool send = Parent->sendMessage(mess,user);
        if (!send)
        {
            // send failed!
        }
    }
    else
    {
        //cant longer than 512!
    }
    sendLineEdit->clear();
}

void Chatroom::CreateRoom()
{
    if(userNameLineEdit->text()=="")
        return ;
    QString name= userNameLineEdit->text();
    if (name.length() <= 16)
    {
        if (!Parent->host && !Parent->waiting && !Parent->inRooms)
        {
            std::string user = userNameLineEdit->text().toStdString();
            bool send = Parent->CreateRoom(user);
            if (!send)
            {
            // send failed!
            }
        }
    }
    else
    {
        // name is so long!
    }
}
