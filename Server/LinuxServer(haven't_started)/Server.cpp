#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically) //Port = port to broadcast on. BroadcastPublically = false if server is not open to the public (people outside of your router), true = server is open to everyone (assumes that the port is properly forwarded on router settings)
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (BroadcastPublically) //If server is open to public
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else //If server is only for our router
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(PORT); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) //Bind the address to the socket, if we fail to bind the address..
	{
		string ErrorMsg = "Failed to bind the address to our listening socket. Winsock Error:" + to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections, if we fail to listen on listening socket...
	{
		string ErrorMsg = "Failed to listen on listening socket. Winsock Error:" + to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	serverptr = this;
}

bool Server::SendString(int ID, string & _string)
{
	int RetnCheck = send(Connections[ID], _string.c_str(), 512, NULL); //Send string buffer
	if (RetnCheck == SOCKET_ERROR) //If failed to send string buffer
		return false; //Return false: Failed to send string buffer
	return true; //Return true: string successfully sent
}

bool Server::GetString(int ID, string & _string)
{
	char buffer[512];
	int RetnCheck = recv(Connections[ID], buffer, 512, NULL);
	_string = buffer;
	// TO DO:
	// when recv failed ,delete it!
	if (RetnCheck == SOCKET_ERROR)
		return false;
	cout << "get:" << endl << _string << endl;
	return true;
}

void Server::sendMessToClients(string Message)
{
	cout << "send:" << endl << Message << endl;
	unordered_map<int, SOCKET>::iterator it;
	for (it = Connections.begin(); it != Connections.end(); ++it)
	{
		if (!SendString(it->first, Message)) //Send message to connection at index i, if message fails to be sent...
			cout << "Failed to send message to client ID: " << it->first << endl;
	}
	//----------------------------old loop-----------------------------------------------------------
	//for (int i = 0; i < TotalConnections; i++)
	//{
	//	//if (i == ID) //If connection is the user who sent the message...
	//		//continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.

	//	if (!SendString(i, Message)) //Send message to connection at index i, if message fails to be sent...
	//		cout << "Failed to send message to client ID: " << i << endl;
	//}
	//-----------------------------------------------------------------------------------------------
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) //If accepting the client connection failed
	{
		cout << "Failed to accept the client's connection." << endl;
		return false;
	}
	else //If client connection properly accepted
	{
		cout << "Client Connected! ID:" << allID << endl;
		Connections.insert(pair<int, SOCKET>(allID, newConnection));
		//Connections[TotalConnections] = newConnection; //Set socket in array to be the newest connection before creating the thread to handle this client's socket.
		///////////////////////////WRONG CODE//////////////////////////////////////////////
		//_beginthread((_beginthread_proc_type)ClientHandlerThread, NULL, (void*)&TotalConnections);
		//------------------------------
		// this is very interesting! because we use totalconnections' address, so in thread, it became the number++ because of we did it next.
		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------
		_beginthread((_beginthread_proc_type)ClientHandlerThread, NULL, (void*)allID);
		string MOTD = "MOTD: Welcome! This is the message of the day!.";
		SendString(allID, MOTD);
		player newPlayer(new Player(allID));
		PlayerList.insert(pair<int, player>(allID, newPlayer));
		sendGameList(allID);
		allID++;
		TotalConnections += 1; //Incremenent total # of clients that have connected
		return true;
	}
}

bool Server::Processinfo(int ID)
{

	string Message; //string to store our message we received
	if (!GetString(ID, Message)) //Get the chat message and store it in variable: Message
		return false; //If we do not properly get the chat message, return false
					  //Next we need to send the message out to each user
	cJSON *json, *json_type;
	json = cJSON_Parse(Message.c_str());
	json_type = cJSON_GetObjectItem(json, "Type");
	if (json_type == NULL)
	{
		sendMessToClients(Message);
		cout << "Processed chat message packet from user ID: " << ID << endl;
		cJSON_Delete(json);
		return true;
	}
	else
	{
		string type = json_type->valuestring;
		if (type == "Message")
			sendMessToClients(Message);
		else if (type == "CreateRoom")
		{
			if (GameList.size() >= 6)
			{
				cJSON_Delete(json);
				sendSystemInfo(ID, "List_Full");
				return true;
			}
			if (PlayerList[ID]->isFree())
			{
				cJSON *Username;
				Username = cJSON_GetObjectItem(json, "User");
				int gameID = GameNum;
				GameNum++;
				onlineGame newGame(new Game(gameID, ID, Username->valuestring));
				PlayerList[ID]->hostGame(gameID, newGame);
				newGame->hostIs(PlayerList[ID]);
				GameList.insert(pair<int, onlineGame>(gameID, newGame));
				sendSystemInfo(ID, "WaitingForSomeoneJoining");
				sendGameList(-1);
			}
			else
			{
				cout << "The player is already in game!" << endl;
				cJSON_Delete(json);
				return true;
			}
		}
		else if (type == "PlayAgain")
		{
			if (PlayerList[ID]->AreYouInGame() >= 0)
			{
				int HID = PlayerList[ID]->AreYouInGame();
				std::cout << "booltest first" << std::endl;
				GameList[HID]->booltest();
				GameList[HID]->playAgain(ID);
				int anotherPlayer = GameList[HID]->anotherPlayerID(ID);
				if (anotherPlayer >= 0)
				{
					if (GameList[HID]->can_Play_again())
					{
						if (sendSystemInfo(ID, "PlayAgain") && sendSystemInfo(anotherPlayer, "PlayAgain"))
							GameList[HID]->reset_play_again();
					}
				}
				else
					GameList[HID]->reset_play_again();
			}
		}
		else if (type == "move")
		{
			if (PlayerList[ID]->AreYouInGame() >= 0)
			{
				cout << "yes, I am in game" << endl;
				int HID = PlayerList[ID]->AreYouInGame();
				int anotherPlayer = GameList[HID]->anotherPlayerID(ID);
				if (anotherPlayer >= 0)
				{
					cout << "yes, I have palyer" << endl;
					SendString(anotherPlayer, Message);
				}
			}
		}
		else if (type == "JoinRoomRequest")
		{
			cJSON *Games_ID;
			Games_ID = cJSON_GetObjectItem(json, "ID");
			cJSON *Username;
			Username = cJSON_GetObjectItem(json, "User");
			int gameID = Games_ID->valueint;
			string p2name = Username->valuestring;
			cout << "got Join room request from ID: " << Games_ID->valueint << endl;
			// TO DO:
			// if game is nolonger exist
			// send message RoomClose
			// return
			if (GameList[gameID]->isFull())
			{
				sendSystemInfo(ID, "RoomFull");
				cJSON_Delete(json);
				return true;
			}
			else if (GameList[gameID]->hostsID() == ID)
			{
				cJSON_Delete(json);
				return true;
			}
			else
			{
				GameList[gameID]->Joinin(ID, PlayerList[ID], p2name);
				PlayerList[ID]->JoininGame(gameID, GameList[gameID]);
				sendGameList(-1);
				int hostID = GameList[gameID]->hostsID();
				sendSystemInfo(hostID, "HostStartPlaying");
				if(sendSystemInfo(ID, "JoinRoom"))
					sendSystemInfo(hostID, "SomeoneJoin_Successfully");
			}
		}
		else if (type == "BackToLobby")
		{
			if (PlayerList[ID]->AreYouInGame() >= 0)
			{
				int HID = PlayerList[ID]->AreYouInGame();
				int anotherPlayer = GameList[HID]->anotherPlayerID(ID);
				if (anotherPlayer >= 0)
				{
					sendSystemInfo(anotherPlayer, "ReturnTolobby");
					PlayerList[anotherPlayer]->returnToLobby();
				}
				PlayerList[ID]->returnToLobby();
				GameList.erase(HID);
				sendGameList(-1);
			}
			else
				PlayerList[ID]->returnToLobby();
		}
		else if (type == "CancelHost")
		{
			if (PlayerList[ID]->AreYouInGame() >= 0)
			{
				int HID = PlayerList[ID]->AreYouInGame();
				int anotherPlayer = GameList[HID]->anotherPlayerID(ID);
				if (anotherPlayer >= 0)
				{
					sendSystemInfo(anotherPlayer, "ReturnTolobby");
					PlayerList[anotherPlayer]->returnToLobby();
				}
				PlayerList[ID]->returnToLobby();
				GameList.erase(HID);
				sendGameList(-1);
			}
			else
				PlayerList[ID]->returnToLobby();
		}
		else if (type == "Exit")
			return false;
	}
	cout << "Processed chat message packet from user ID: " << ID << endl;
	cJSON_Delete(json);
	return true;
}

bool Server::CreateGameList(string & _string)
{
	cJSON *json = cJSON_CreateObject();
	if (cJSON_AddStringToObject(json, "Type", "List_of_Rooms") == NULL)
	{
		cout << "type add failed." << endl;
		cJSON_Delete(json);
		return false;
	}
	cJSON * Lists = NULL;
	Lists = cJSON_AddArrayToObject(json, "List");
	if (Lists == NULL)
	{
		cout << "List add failed." << endl;
		cJSON_Delete(json);
		return false;
	}
	//if (GameList.size() == 0)
	//{
	//	_string = "NULL";
	//	return true;
	//}
	unordered_map<int, onlineGame>::iterator it;
	for (it = GameList.begin(); it != GameList.end(); ++it)
	{
		cJSON *GAME = cJSON_CreateObject();

		if (cJSON_AddStringToObject(GAME, "name", it->second->hostName.c_str()) == NULL)
		{
			cJSON_Delete(json);
			return false;
		}
		if (cJSON_AddNumberToObject(GAME, "id", it->second->id) == NULL)
		{
			cJSON_Delete(json);
			return false;
		}
		if (cJSON_AddNumberToObject(GAME, "isplay", it->second->isplay) == NULL)
		{
			cJSON_Delete(json);
			return false;
		}
		string p2name;
		if (it->second->isplay)
			p2name = it->second->p2Name;
		else
			p2name = "";
		if (cJSON_AddStringToObject(GAME, "p2name", p2name.c_str()) == NULL)
		{
			cJSON_Delete(json);
			return false;
		}
		cJSON_AddItemToArray(Lists, GAME);
	}

	_string = cJSON_Print(json);
	cJSON_Delete(json);
	return true;;
}

bool Server::sendSystemInfo(int ID, string InfoType)
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddStringToObject(json, "Type", "System");
	cJSON_AddStringToObject(json, "System_Info", InfoType.c_str());
	char *JsonToSend = cJSON_Print(json);
	cJSON_Delete(json);
	cout << "send:" << endl << JsonToSend << " To: " << ID << endl;
	string Send(JsonToSend);
	return SendString(ID, Send);
}

bool Server::sendGameList(int ID)
{
	string Message;
	if (!CreateGameList(Message))
	{
		cout << "create game list JSON failed!" << endl;
		return false;
	}
	if (Message == "NULL")
		return true;
	if (ID < 0)
		sendMessToClients(Message);
	else
		SendString(ID, Message);
	return true;
}


void Server::ClientHandlerThread(void* IDstar) //ID = the index in the SOCKET Connections array
{
	int ID = (int)IDstar;
	while (true)
	{
		if (!serverptr->Processinfo(ID))
			break;
	}
	cout << "Lost connection to client ID: " << ID << endl;
	closesocket(serverptr->Connections[ID]);
	if (serverptr->PlayerList[ID]->AreYouInGame() >= 0)
	{
		cout << "delete its game room: " <<  endl;
		int HID = serverptr->PlayerList[ID]->AreYouInGame();
		int anotherPlayer = serverptr->GameList[HID]->anotherPlayerID(ID);
		if (anotherPlayer >= 0 && serverptr->PlayerList[anotherPlayer])
		{
			serverptr->sendSystemInfo(anotherPlayer, "LostConnection");
			serverptr->PlayerList[anotherPlayer]->returnToLobby();
		}
		serverptr->GameList.erase(HID);
		serverptr->sendGameList(-1);
	}
	serverptr->PlayerList.erase(ID);
    serverptr->Connections.erase(ID);
	serverptr->TotalConnections-=1;
}