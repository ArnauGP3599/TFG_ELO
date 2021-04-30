#pragma once
#include "Player.h"

class PlayersDB
{
public:
	void init();
	void addPlayers(int numPlayers);

	vector<shared_ptr<Player>> getPlayers();

	int getPlayersSize();

private:
	vector<shared_ptr<Player>> players;
};

