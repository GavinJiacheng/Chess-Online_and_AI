#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "Games.h"


typedef std::shared_ptr<Game> onlineGame;

class Player
{
public:
	Player(int id)
	{
		this->id = id;
	}
	void JoininGame(int GameID, onlineGame GAME)
	{
		this->GameID = GameID;
		ingame = true;
		this->game = GAME;
	}
	void hostGame(int gameID, onlineGame GAME)
	{
		this->GameID = gameID;
		this->game = GAME;
		ishost = true;
		//ingame = true;
	}
	void returnToLobby()
	{
		ishost = false;
		ingame = false;
		GameID = -1;
		game = NULL;
	}
	bool isFree()
	{
		return !ishost && !ingame;
	}
	int AreYouInGame()
	{
		return GameID;
	}
private:
	int id;
	int GameID = -1;
	onlineGame game = NULL;
	bool ishost = false;
	bool ingame = false;
};