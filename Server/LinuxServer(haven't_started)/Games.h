#pragma once

#include <string>
#include <iostream>
#include <memory>


class Player;
typedef std::shared_ptr<Player> player;

class Game
{
public:
	friend class Server;
	Game(int id, int host_id, std::string host_name)
	{
		this->id = id;
		this->host_id = host_id;
		this->hostName = host_name;
	}
	void Joinin(int joinID, player Join_player, std::string p2Name)
	{
		this->guest_id = joinID;
		player2 = Join_player;
		this->p2Name = p2Name;
		isplay = 1;
	}
	void playAgain(int playID)
	{
		if (playID == host_id)
			host_play_again = true;
		else
			player2_play_again = true;
	}
	bool can_Play_again()
	{
		return (host_play_again && player2_play_again);
	}
	void reset_play_again()
	{
		host_play_again = false;
		player2_play_again = false;
	}
	void hostIs(player host)
	{
		this->host = host;
	}
	bool isFull()
	{
		return (guest_id != -1);
	}
	int hostsID()
	{
		return host_id;
	}
	int anotherPlayerID(int onePlayerID)
	{
		if (onePlayerID == host_id)
			return guest_id;
		else if (onePlayerID == guest_id)
			return host_id;
		else
			return -1;
	}
	void booltest()
	{
		if (host_play_again)
			std::cout << "host_play_again is TRUE" << std::endl;
		else
			std::cout << "host_play_again is FALSE" << std::endl;
		if (player2_play_again)
			std::cout << "player2_play_again is TRUE" << std::endl;
		else
			std::cout << "player2_play_again is FALSE" << std::endl;
	}
private:
	int id;
	int host_id;
	std::string hostName;
	std::string p2Name;
	int guest_id = -1;
	int isplay = 0;
	bool host_play_again = false;
	bool player2_play_again = false;
	player host = NULL;
	player player2 = NULL;
};