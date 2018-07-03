#ifndef GAMELOBBY_H
#define GAMELOBBY_H




//#define WIN32_LEAN_AND_MEAN  //add this line to your Qt's include\QtCore\qt_windows.h, before #include <windows.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QCloseEvent>
#include <cstring>
#include <WinSock2.h>
#include <windows.h>
#include <process.h>


#include "cJSON/cJSON.h"
#include "chatroom.h"
#include "chessroom.h"
#include "onlinemove.h"
#include "button.h"

#pragma comment(lib, "ws2_32.lib")

class gameLobby:public QGraphicsView
{
    Q_OBJECT
public:
    gameLobby(QWidget *parent =0);
    ~gameLobby();
    bool connectError = false;
    void connectToServer();
    static bool is_opened;
    bool CloseConnection();
    bool sendMove(int FromX, int FromY, int ToX, int ToY);
    bool sendMove(int FromX, int FromY, int ToX, int ToY, int castling);
    friend class Chatroom;
    friend class ChessRoom;
    friend class game;
    int yourSide = -1;
    //SignaL_XXXX means send signal for XXXX
    void Signal_socketClosed();
    void Signal_socketClosedfailed();
    void Signal_TimeoutJoin();
    bool backToLobby();

signals:
    void updateRooms(cJSON *Lists);
    void socketClosed();
    void socketClosedfailed();
    void TimeoutJoin();
    void someoneLeave();
    void ShowGame();
    void PlayWhite();
    void PlayBlack();
    void moveTo(onlineMove*); // need to be done
    void Full();
    void RoomClose(); // need to be done;
    void ListFull();

protected:
    void closeEvent(QCloseEvent *event);

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
    bool host = false;
    bool waiting = false;
    bool connection = false;
    QGraphicsScene* OnlineScene;
    QGraphicsTextItem *titleText;
    button * playButton;
    bool sendMessage(const std::string& message, const std::string& username);
    bool CreateRoom(const std::string& user);
    bool GetString();
    Chatroom* chRoom;
    void SendRequestForJoining(int ID);
    QList <ChessRoom*> chessroomS;
    void exitLobby();
    void showRooms();
    void LobbySUI();
    void waitingForJoin(); //nedd to be done
    void hostWindow();
    QGraphicsRectItem *rect;
    QGraphicsTextItem *WindowTitle;
    button * CancelBotton;
    void hostWindow_hide();
    void hostWindow_show();

    //void CancelWaiting(); //need to be done
        //void sendMessage(string message);

public slots:
    void createRoomsList(cJSON *Lists);
    void sendJointRequest(int ID);
    void ServerClose();
    void SocketBugs();
    void JoinTimeOut();
    void Leave();
    void List_is_full();
    void This_Game_isFull();
    void I_wannaPlayAgain();
    void ReturnToMenu();
    void CancelHost();


};


#endif // GAMELOBBY_H
