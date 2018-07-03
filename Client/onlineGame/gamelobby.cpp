#include "gamelobby.h"

#include <QMessageBox>
#include <QDebug>

#include <mutex>
#include "game.h"



#define MAXSIZE 512

#pragma execution_character_set("utf-8")
static gameLobby * clientptr;
bool gameLobby::is_opened = false;
extern game* Game;


gameLobby::gameLobby(QWidget *parent):QGraphicsView(parent)
{
    gameLobby::is_opened = true;
    OnlineScene = new QGraphicsScene();
    OnlineScene->setSceneRect(0,0,1400,940);

    //Making the view Full()
    setFixedSize(1400,950);
    setScene(OnlineScene);
    clientptr = this;
    chRoom = new Chatroom(this);
    connect(this, SIGNAL(updateRooms(cJSON*)) , this , SLOT(createRoomsList(cJSON*)));
    connect(this, SIGNAL(socketClosed()) , this , SLOT(ServerClose()));
    connect(this, SIGNAL(socketClosedfailed()) , this , SLOT(SocketBugs()));
    connect(this, SIGNAL(TimeoutJoin()) , this , SLOT(JoinTimeOut()));
    connect(this, SIGNAL(ListFull()), this, SLOT(List_is_full()));
    connect(this, SIGNAL(Full()), this, SLOT(This_Game_isFull()));
    connect(this, SIGNAL(someoneLeave()), this, SLOT(Leave()));
    connect(this, SIGNAL(ShowGame()), Game, SLOT(SHOW()));
    connect(this, SIGNAL(PlayBlack()), Game, SLOT(palyAsBlackOnline()));
    connect(this, SIGNAL(PlayWhite()), Game, SLOT(palyAsWhiteOnline()));
    connect(this, SIGNAL(moveTo(onlineMove*)), Game, SLOT(receiveMove(onlineMove*)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connectToServer();
    if (connectError)
        return;
    titleText = new QGraphicsTextItem("Online Chess Lobby");
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    //show!
    OnlineScene->addItem(titleText);
    playButton = new button("Return to Menu");
    int pxPos = 150;
    int pyPos = 850;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(ReturnToMenu()));
    playButton->hide();
    OnlineScene->addItem(playButton);
    hostWindow();
    LobbySUI();
    chRoom->show();

    // for test:
    //createRoomsList();
    //SetGamecolor();
}

gameLobby::~gameLobby()
{
    gameLobby::is_opened = false;
}



void gameLobby::connectToServer()
{
    sockVersion = MAKEWORD(2, 1);
    //qDebug() << "create the sockVersion.";
    if (WSAStartup(sockVersion, &wsaData)){
        //winsock startup failed;
        QMessageBox::critical(NULL, "Error", "Winsock startup failed");
        connectError = true;
        return;
    }
    //qDebug() << "Winsock start.";
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //server's address
    addr.sin_port = htons(1111); // Server's port
    addr.sin_family = AF_INET; //IPV4 socket
    Connection = socket(AF_INET, SOCK_STREAM, NULL); //create Connection socket

        // you need ::connect rather than the connect because in Qt they have a fucntion called connect which is for signal

    if (::connect(Connection, (SOCKADDR*)&addr, sizeofaddr)) //If we have trouble in connect to the addr
    {
       // MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
        QMessageBox::critical(NULL, "Error", "Failed to Connect");
        connectError = true;
        return;
    }
    //qDebug() << "Connect done.";
    _beginthread((_beginthread_proc_type)ClientThread, NULL, NULL); //Create the client thread that will receive any data that the server sends.
    //qDebug() << "Connected!";
}

bool gameLobby::CloseConnection()
{
    if (closesocket(Connection) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAENOTSOCK) //If socket error is that operation is not performed on a socket (This happens when the socket has already been closed)
            return true; //return true since connection has already been closed

        std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
        QMessageBox::critical(NULL, "Error", ErrorMessage.c_str());
        return false;
    }
    qDebug()<<"b1";
    return true;
}

bool gameLobby::sendMove(int FromX, int FromY, int ToX, int ToY)
{
    //create Json
    cJSON * Move;
    //if !Mesg
    Move=cJSON_CreateObject();
    cJSON_AddStringToObject(Move,"Type","move");
    cJSON_AddNumberToObject(Move,"FromX",FromX);
    cJSON_AddNumberToObject(Move,"FromY",FromY);
    cJSON_AddNumberToObject(Move,"ToX",ToX);
    cJSON_AddNumberToObject(Move,"ToY",ToY);
    cJSON_AddNumberToObject(Move,"Castling",-1);
    char *JsonToSend = cJSON_Print(Move);   //make the json as char*
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool gameLobby::sendMove(int FromX, int FromY, int ToX, int ToY, int castling)
{
    //create Json
    cJSON * Move;
    //if !Mesg
    Move=cJSON_CreateObject();
    cJSON_AddStringToObject(Move,"Type","move");
    cJSON_AddNumberToObject(Move,"FromX",FromX);
    cJSON_AddNumberToObject(Move,"FromY",FromY);
    cJSON_AddNumberToObject(Move,"ToX",ToX);
    cJSON_AddNumberToObject(Move,"ToY",ToY);
    cJSON_AddNumberToObject(Move,"Castling",castling);
    char *JsonToSend = cJSON_Print(Move);   //make the json as char*
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    return true;
}

void gameLobby::Signal_socketClosed()
{
    emit socketClosed();
}

void gameLobby::Signal_socketClosedfailed()
{
    emit socketClosedfailed();
}

void gameLobby::Signal_TimeoutJoin()
{
    emit TimeoutJoin();
}

void gameLobby::I_wannaPlayAgain()
{
    cJSON * Mesg;
    //if !Mesg
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","PlayAgain");
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    //if (RetnCheck == SOCKET_ERROR)
        //return false;
    //return true;
}

void gameLobby::ReturnToMenu()
{
    if (!inRooms && !waiting && !host)
    {
        gameLobby::is_opened = false;
        Game->mainmenu();
        exitLobby();
        Game->show();
        this->close();
    }
}


void gameLobby::CancelHost()
{
    cJSON * Mesg;
    //if !Mesg
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","CancelHost");
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    if (send(Connection, JsonToSend, MAXSIZE, NULL))
    {
        yourSide = -1;
        inRooms = false;
        waiting = false;
        host = false;
        showRooms();
    }
}

bool gameLobby::backToLobby()
{
    cJSON * Mesg;
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","BackToLobby");
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    else
    {
        clientptr->host = false;
        clientptr->inRooms = false;
        clientptr->waiting = false;
        clientptr->yourSide = -1;
        showRooms();
        return true;
    }
}

void gameLobby::closeEvent(QCloseEvent *event)
{
    gameLobby::is_opened = false;
    if(inRooms)
        Game->mainmenu();
    exitLobby();
    chRoom->close();
    event->accept();
}

bool gameLobby::sendMessage(const std::string& message, const std::string& username)
{

    //create Json
    cJSON * Mesg;
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","Message");
    cJSON_AddStringToObject(Mesg,"User",username.c_str());
    cJSON_AddStringToObject(Mesg,"Message",message.c_str());
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool gameLobby::CreateRoom(const std::string &user)
{
    //test
    //const char* JsonToSend= "{\"Type\":\"List_of_Rooms\", \"List\":[{\"name\":\"xiaohong\",\"id\":3,\"isplay\":0}]}";

    host = true;
    waitingForJoin();
    //create Json
    cJSON * Mesg;
    //if !Mesg
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","CreateRoom");
    cJSON_AddStringToObject(Mesg,"User",user.c_str());
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    //TO DO:
    //waiting for others
    //inplay
    return true;
}

bool gameLobby::GetString()
{
    char buffer[MAXSIZE];
    int RetnCheck = recv(Connection, buffer, sizeof(buffer), NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    //analize JSON:
    cJSON *json, *json_type;
        //if !json
        //if !json_type
    json = cJSON_Parse(buffer);
    json_type = cJSON_GetObjectItem(json , "Type");
	if (json_type == NULL)
	{
        this->chRoom->Showmessage(buffer);
        cJSON_Delete(json);
		return true;
	}
    std::string type = json_type->valuestring;
    if (type == "Message")
	{
        cJSON *Mess;
		Mess = cJSON_GetObjectItem(json, "Message");
        this->chRoom->Showmessage(Mess->valuestring);
        cJSON_Delete(json);
		return true;
	}
    else if (type == "List_of_Rooms")
    {
        //get list;
        //cJSON *List;
        //List = cJSON_GetObjectItem(json, "List");
        //if (!List)

        //If you are not good at Qt, you must remember, never use threads except the main thread to create an item for UI.
        // you must use signals and slots

        emit updateRooms(json);
        //createRoomsList(List);
    }
    else if (type == "move")
    {
        if (inRooms)
        {
            cJSON *FromX,*FromY,*ToX,*ToY, *Castling;
            FromX = cJSON_GetObjectItem(json, "FromX");
            FromY = cJSON_GetObjectItem(json, "FromY");
            ToX = cJSON_GetObjectItem(json, "ToX");
            ToY = cJSON_GetObjectItem(json, "ToY");
            Castling = cJSON_GetObjectItem(json, "Castling");
            onlineMove *Move = new onlineMove(FromX->valueint,FromY->valueint,ToX->valueint,ToY->valueint,Castling->valueint);
            cJSON_Delete(json);
            emit moveTo(Move);
            Move = NULL;
        }
    }
    else if (type == "System")
    {
        cJSON *System_Info;
        System_Info = cJSON_GetObjectItem(json, "System_Info");
        std::string systemInfo =System_Info->valuestring;
        if (systemInfo == "SomeoneJoin_Successfully")
        {
            //signal
            emit ShowGame();
        }
        else if (systemInfo == "HostStartPlaying")
        {
            yourSide = 0;
            inRooms = true;
            clientptr->waiting = false;
            //signal
            emit PlayWhite();
        }
        // server should send JoinRoom first then send SomeoneJoining
        else if (systemInfo == "JoinRoom")
        {
            // this join room means you join the room successfully
            yourSide = 1;
            inRooms = true;
            clientptr->waiting = false;
            //signal
            emit PlayBlack();
            emit ShowGame();
        }
        else if (systemInfo == "PlayAgain")
        {
            if (yourSide == 1) // you are playing black
                emit PlayBlack();
            else
                emit PlayWhite();
        }
        else if (systemInfo == "RoomClose")
        {
                emit RoomClose();
            // this means this room is no longer exist
        }
        else if (systemInfo == "LostConnection")
        {
            //should be the host lost or\ the guest lost
            //You need use go back to the lobby here;
            emit someoneLeave();
        }
        else if (systemInfo == "RoomFull")
        {
            clientptr->waiting = false;
            emit Full();
            // when you are join a room, someone join it before you
        }
        else if (systemInfo == "List_Full")
        {
            clientptr->waiting = false;
            emit ListFull();
        }
        else if (systemInfo == "WaitingForSomeoneJoining")
        {
            clientptr->host = true;
            // TO DO:
            // waiting for others joing
        }
        else if (systemInfo == "ReturnTolobby")
        {
            emit someoneLeave();
        }
        cJSON_Delete(json);

        //when leave room, you need to reset yourSide = -1, inRooms = false, and hide game again.
        // and clientptr->host = false;!!!
    }
    return true;
}

void gameLobby::createRoomsList(cJSON *json)
{

    qDeleteAll(chessroomS);
    chessroomS.clear();

    cJSON *List;
    List = cJSON_GetObjectItem(json, "List");
    ChessRoom *NewChess;
    int array_size = cJSON_GetArraySize(List);
    cJSON *chessroomINFO = NULL; //init cJSON


    if (array_size == 0)
    {
        cJSON_Delete(json);
        return;
    }

    cJSON_ArrayForEach(chessroomINFO, List)
    {

        //when the thread is doing this, it should be locked.
        bool playing = false;
        cJSON *Name = cJSON_GetObjectItem(chessroomINFO, "name");
        cJSON *ID = cJSON_GetObjectItem(chessroomINFO, "id");
        cJSON *isPlaying = cJSON_GetObjectItem(chessroomINFO, "isplay");

        if(isPlaying->valueint)
            playing = true;
        else
            playing = false;
        NewChess = new ChessRoom(this, Name->valuestring, ID->valueint, playing);
        if (playing)
        {
            cJSON *P2 = cJSON_GetObjectItem(chessroomINFO, "p2name");
            NewChess->player2(P2->valuestring);
        }

        chessroomS.append(NewChess);
    }
    cJSON_Delete(json);

    //test:--------------------------------------------------------
    //NewChess = new ChessRoom(this, "Gavin", 3, false);
    //chessroomS.append(NewChess);
    //NewChess = new ChessRoom(this, "Gavin", 3, false);
    //chessroomS.append(NewChess);
    //NewChess = new ChessRoom(this, "Gavin", 3, false);
    //chessroomS.append(NewChess);
    //-----------------------------------------------------------------

    // create signal!
    // ------------------------
    // This is very important
    //----------------------------------

    //emit updateRooms();
    showRooms();
}

void gameLobby::showRooms()
{
    //OnlineScene->clear(); //badass here
    LobbySUI();
    waitingForJoin();

    int len = chessroomS.length();
    for (int i =0; i<len; i++)
    {
        connect(chessroomS[i], SIGNAL(clicked(int)) , this , SLOT(sendJointRequest(int)));
        chessroomS[i]->setPos(300+(i%3)*300,300+(i/3)*240);
        this->OnlineScene->addItem(chessroomS[i]);
    }
}

void gameLobby::LobbySUI()
{
    if (!inRooms && !waiting && !host)
        playButton->show();
    else
        playButton->hide();
}


void gameLobby::waitingForJoin()
{
    if (host)
        hostWindow_show();
    else
        hostWindow_hide();
}

void gameLobby::hostWindow()
{
    rect = new QGraphicsRectItem();
    rect->setRect(0,0,450,300);
    QBrush Abrush;
    Abrush.setStyle(Qt::SolidPattern);
    Abrush.setColor(QColor(199, 231, 253));
    rect->setBrush(Abrush);
    rect->setZValue(4);
    int pxPos = width()/2 - rect->boundingRect().width()/2;
    int pyPos = 250;
    rect->setPos(pxPos,pyPos);
    WindowTitle = new QGraphicsTextItem("Wating for other Players...");
    QFont titleFont("arial" , 20);
    WindowTitle->setFont( titleFont);
    int axPos = width()/2 - WindowTitle->boundingRect().width()/2;
    int ayPos = 300;
    WindowTitle->setPos(axPos,ayPos);
    WindowTitle->setZValue(5);
    CancelBotton = new button("Cancel Host");
    int qxPos = width()/2 - CancelBotton->boundingRect().width()/2;
    int qyPos = 400;
    CancelBotton->setPos(qxPos,qyPos);
    CancelBotton->setZValue(5);
    connect(CancelBotton,SIGNAL(clicked()) , this , SLOT(CancelHost()));
    hostWindow_hide();
    OnlineScene->addItem(rect);
    OnlineScene->addItem(WindowTitle);
    OnlineScene->addItem(CancelBotton);
}

void gameLobby::hostWindow_hide()
{
    rect->hide();
    WindowTitle->hide();
    CancelBotton->hide();
}

void gameLobby::hostWindow_show()
{
    rect->show();
    WindowTitle->show();
    CancelBotton->show();
}

//this is sooooo stupid, how can you make this stupid idea>??>??????

void gameLobby::sendJointRequest(int ID)
{
    if (!inRooms && !waiting && !host)
    {
       this->SendRequestForJoining(ID);
    }
}

void gameLobby::SendRequestForJoining(int ID)
{
    //create Json
    cJSON * Request;
    //if !Request
    Request=cJSON_CreateObject();
    cJSON_AddStringToObject(Request,"Type","JoinRoomRequest");
    cJSON_AddStringToObject(Request,"User", chRoom->userNameLineEdit->text().toStdString().c_str());
    cJSON_AddNumberToObject(Request,"ID",ID);

    char *JsonToSend = cJSON_Print(Request);   //make the json as char*
    cJSON_Delete(Request);
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
    {
        //TO DO: failed send;
        return;
    }
    _beginthread((_beginthread_proc_type)WaitforResponseThread, NULL, NULL);
}

void gameLobby::exitLobby()
{
    cJSON * Mesg;
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","Exit");
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    cJSON_Delete(Mesg);
    send(Connection, JsonToSend, MAXSIZE, NULL);
    //int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    //if (RetnCheck == SOCKET_ERROR)
        //return false;
    //return true;
}


void gameLobby::WaitforResponseThread()
{
    //this is thread safe
    clientptr->waiting = true;
    Sleep(4000);
    if (clientptr->waiting)
    {
        //Join in Room failed!
        //TO DO: add something here!
        qDebug()<<"Join Room time out!";
        clientptr->Signal_TimeoutJoin();
        clientptr->waiting = false;
    }
}

void gameLobby::JoinTimeOut()
{
    QMessageBox::information(NULL, "Time Out", "Join Room time out.");
}

void gameLobby::Leave()
{
    host = false;
    inRooms = false;
    waiting = false;
    yourSide = -1;
    Game->hide();
    Game->mainmenu();
    showRooms();
    QMessageBox::information(NULL, "Game is end", "The host or player already left the room.");
}

void gameLobby::List_is_full()
{
    QMessageBox::information(NULL, "List Full", "The max amount of Chess Games is 6.");
}

void gameLobby::This_Game_isFull()
{
    QMessageBox::information(NULL, "Game is Full", "This Game is already started.");
}


void gameLobby::ServerClose()
{
    QMessageBox::information(NULL, "Server closed", "Socket to the server was closed successfuly.");
}

void gameLobby::SocketBugs()
{
    QMessageBox::warning(NULL, "Socket has problem", "Socket was not able to be closed.");
}


void gameLobby::ClientThread()
{
    while (true)
    {
        //qDebug() << "Thread start.";
        if (!is_opened)
            return;
        if (!clientptr->GetString())
            break;
    }
    //qDebug() << "Lost connection to the server.";
    if (clientptr->CloseConnection()) //Try to close socket connection..., If connection socket was closed properly
         clientptr->Signal_socketClosed();
    //"Widgets must be created in the GUI thread.", file kernel\qwidget.cpp, line 1144
    else //If connection socket was not closed properly for some reason from our function
        clientptr->Signal_socketClosedfailed();
}
