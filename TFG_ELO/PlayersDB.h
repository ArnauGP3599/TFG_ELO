#pragma once
#include "Player.h"

class PlayersDB
{
public:
	void init();
	void addPlayers(int numPlayers);

	vector<shared_ptr<Player>> getPlayers();

private:
	vector<shared_ptr<Player>> players;
};

