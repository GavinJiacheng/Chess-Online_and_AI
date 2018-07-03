#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <memory>
#include <iostream>
#include <process.h>
#include "Games.h"
#include "Player.h"
#include <unordered_map>
#include "cJSON\cJSON.h"

//typedef std::vector<std::vector<unique_ptr>> BOARD;

using namespace std;

typedef shared_ptr<Game> onlineGame;
typedef shared_ptr<Player> player;


class Server
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:
	bool SendString(int ID, string & _string);
	bool GetString(int ID, string & _string);
	void sendMessToClients(string Message);
	bool Processinfo(int ID);
	bool CreateGameList(string & _string);
	bool sendSystemInfo(int ID, string InfoType);
	bool sendGameList(int ID); // if ID <0 ,means send gamelist to all clients
	void deleteGame(int ID);

	static void ClientHandlerThread(void* IDptr);

private:
	//-------------------------------------------
	// online variables:
	//-------------------------------------------
	unordered_map<int, SOCKET> Connections;
	//SOCKET Connections[512];
	int TotalConnections = 0;
	int allID = 0;
	SOCKADDR_IN addr;                //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
	//---------------------------------------
	//Logic variables:
	//----------------------------------------
	int GameNum = 0;
	unordered_map<int, onlineGame> GameList;
	unordered_map<int, player> PlayerList;
};

static Server * serverptr; 