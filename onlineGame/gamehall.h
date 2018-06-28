#ifndef GAMEHALL_H
#define GAMEHALL_H




//#define WIN32_LEAN_AND_MEAN  //add this line to your Qt's include\QtCore\qt_windows.h, before #include <windows.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <cstring>
#include <WinSock2.h>
#include <windows.h>
#include <process.h>

#include "cJSON/cJSON.h"
#include "chatroom.h"
#include "chessroom.h"

#pragma comment(lib, "ws2_32.lib")





class gameHall:public QGraphicsView
{
    Q_OBJECT
public:
    gameHall(QWidget *parent = NULL);
    ~gameHall();
    bool connectError = false;
    void connectToServer();
    static bool is_opened;
    bool CloseConnection();
    friend class Chatroom;
    friend class ChessRoom;

signals:
    void updateRooms(cJSON *Lists);

public slots:
    //void ChosseRoom();
    //void Exit();
private:
    int prot = 1111;
    static void ClientThread();
    static void WaitforResponseThread();
    WSAData wsaData;
    WORD sockVersion;
    SOCKADDR_IN addr;
    SOCKET Connection;
    int numOfRooms = 0;
    bool inRooms = false;
    bool waiting = false;
    bool connection = false;
    QGraphicsScene* OnlineScene;
    bool sendMessage(const std::string& message, const std::string& username);
    bool CreateRoom(const std::string& user);
    bool GetString();
    Chatroom* chRoom;
    void SendRequestForJoining(int ID);
    QList <ChessRoom*> chessroomS;
        void showRooms();
        //void sendMessage(string message);

public slots:
    void createRoomsList(cJSON *Lists);
    void sendJointRequest(int ID);



};


#endif // GAMEHALL_H
