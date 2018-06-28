#include "gamehall.h"

#include <QMessageBox>
#include <QDebug>




#define MAXSIZE 512

#pragma execution_character_set("utf-8")
static gameHall * clientptr;
bool gameHall::is_opened = false;
gameHall::gameHall(QWidget *parent):QGraphicsView(parent)
{
    gameHall::is_opened = true;
    OnlineScene = new QGraphicsScene();
    OnlineScene->setSceneRect(0,0,1400,940);

    //Making the view
    setFixedSize(1400,950);
    setScene(OnlineScene);
    clientptr = this;
    chRoom = new Chatroom(this);
    connect(this, SIGNAL(updateRooms(cJSON*)) , this , SLOT(createRoomsList(cJSON*)));
    connectToServer();
    if (connectError)
        return;
    chRoom->show();

    // for test:
    //createRoomsList();
    //SetGamecolor();
}

gameHall::~gameHall()
{
    gameHall::is_opened = false;
}


void gameHall::connectToServer()
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

bool gameHall::CloseConnection()
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

bool gameHall::sendMessage(const std::string& message, const std::string& username)
{

    //create Json
    cJSON * Mesg;
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","Message");
    cJSON_AddStringToObject(Mesg,"User",username.c_str());
    cJSON_AddStringToObject(Mesg,"Message",message.c_str());
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool gameHall::CreateRoom(const std::string &user)
{
    //test
    //const char* JsonToSend= "{\"Type\":\"List_of_Rooms\", \"Lists\":[{\"name\":\"xiaohong\",\"id\":3,\"isplay\":0}]}";


    //create Json
    cJSON * Mesg;
    //if !Mesg
    Mesg=cJSON_CreateObject();
    cJSON_AddStringToObject(Mesg,"Type","CreateRoom");
    cJSON_AddStringToObject(Mesg,"User",user.c_str());
    char *JsonToSend = cJSON_Print(Mesg);   //make the json as char*

    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool gameHall::GetString()
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
		return true;
	}
    std::string type = json_type->valuestring;
	if (type == "Message")
	{
		cJSON *Mess;
		Mess = cJSON_GetObjectItem(json, "Message");
		this->chRoom->Showmessage(Mess->valuestring);
		return true;
	}
    if (type == "List_of_Rooms")
    {
        //get list;
        qDebug() << "bug before lists";
        cJSON *Lists;
        Lists = cJSON_GetObjectItem(json, "Lists");
        //if (!Lists)

        //If you are not good at Qt, you must remember, never use threads except the main thread to create an item for UI.
        // you must use signals and slots

        emit updateRooms(Lists);
        //createRoomsList(Lists);
    }
    if (type == "moves")
    {

    }
    if (type == "System")
    {
        cJSON *System_type;
        System_type = cJSON_GetObjectItem(json, "System_type");
        std::string systemType =System_type->valuestring;
        if (systemType == "JoinRoom")
        {
            inRooms = true;
            clientptr->waiting = false;
        }
        if (systemType == "LostConnection")
        {
            //should be 1, the host lost or\ 2, the guest lost
        }
        if (systemType == "RoomFull")
        {
            clientptr->waiting = false;
            // when you are join a room, someone join it before you
        }
    }
    return true;
}

void gameHall::createRoomsList(cJSON *Lists)
{
    qDeleteAll(chessroomS);
    chessroomS.clear();


    ChessRoom *NewChess;
    int array_size = cJSON_GetArraySize(Lists);
    cJSON *chessroomINFO = NULL; //init cJSON


    if (array_size == 0)
    {
        //TO DO: print empty hall
    }

    cJSON_ArrayForEach(chessroomINFO, Lists)
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

        chessroomS.append(NewChess);
    }

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

void gameHall::showRooms()
{
    OnlineScene->clear();
    int len = chessroomS.length();
    qDebug() << "len: " << len;
    for (int i =0; i<len; i++)
    {
        connect(chessroomS[i], SIGNAL(clicked(int)) , this , SLOT(sendJointRequest(int)));
        chessroomS[i]->setPos(300+(i%3)*300,300+(i/3)*240);
        this->OnlineScene->addItem(chessroomS[i]);
    }
}

void gameHall::sendJointRequest(int ID)
{
    if (!inRooms && !waiting)
    {
       this->SendRequestForJoining(ID);
    }
}

void gameHall::SendRequestForJoining(int ID)
{
    //create Json
    cJSON * Request;
    //if !Request
    Request=cJSON_CreateObject();
    cJSON_AddStringToObject(Request,"Type","JoinRoomRequest");
    cJSON_AddStringToObject(Request,"User", chRoom->userNameLineEdit->text().toStdString().c_str());
    cJSON_AddNumberToObject(Request,"ID",ID);

    char *JsonToSend = cJSON_Print(Request);   //make the json as char*
    int RetnCheck = send(Connection, JsonToSend, MAXSIZE, NULL);
    if (RetnCheck == SOCKET_ERROR)
    {
        //TO DO: failed send;
        return;
    }
    _beginthread((_beginthread_proc_type)WaitforResponseThread, NULL, NULL);
}


void gameHall::WaitforResponseThread()
{
    //this is thread safe
    clientptr->waiting = true;
    Sleep(4000);
    if (clientptr->waiting)
    {
        //Join in Room failed!
        //TO DO: add something here!
        qDebug()<<"Join Room time out!";
        clientptr->waiting = false;
    }
}


void gameHall::ClientThread()
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
         QMessageBox::information(NULL, "Server closed", "Socket to the server was closed successfuly."); //bugs here
    //"Widgets must be created in the GUI thread.", file kernel\qwidget.cpp, line 1144
    else //If connection socket was not closed properly for some reason from our function
        QMessageBox::warning(NULL, "Socket has problem", "Socket was not able to be closed.");
}
