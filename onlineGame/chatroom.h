#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "gamehall.h"
#include "message.h"


class Chatroom: public QDialog
{
    Q_OBJECT
public:
    friend class gameHall;
    Chatroom(gameHall *parent,Qt::WindowFlags f=0);
    QListWidget *contentListWidget;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;
    QPushButton *CreateChessRoomBtn;
    QGridLayout *mainLayout;
    bool status;
    QString userName;
    void Showmessage(char* String);
    friend class gameHall;
    friend class ChessRoom;

    //~Chatroom();
private slots:
    void sendMessage();
    void CreateRoom();
    //void CreateChessRoom();
private:
    gameHall* Parent;

};

#endif // CHATROOM_H
