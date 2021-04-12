#pragma once
#include "Player.h"
#include "PlayersDB.h"
#include "Classification.h"

class Result
{
public:
	void init(shared_ptr<PlayersDB>& playersDB);
	void changeEloPlayers(map<int, EloScore> eloChange);
private:
	shared_ptr<PlayersDB> m_playersDB;
};

