#pragma once
#include "Player.h"
#include "PlayersDB.h"
#include "Classification.h"

class Result
{
public:
	void init(shared_ptr<PlayersDB>& playersDB);
	void changeEloPlayers(pair<int, int> eloChange, shared_ptr<Classification>& classification);
private:
	shared_ptr<PlayersDB> playersDB;
};

