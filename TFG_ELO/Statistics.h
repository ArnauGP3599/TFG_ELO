#pragma once

#include <list>
#include "PlayersDB.h"

class Statistics
{
public:
	void init(shared_ptr<PlayersDB>& i_playersDB);
	void updateStatistics();

	list<vector<int>> getStatistics();

private:
	void writePlayersProperties();
	int m_round;
	list<vector<int>> m_statistics;
	shared_ptr<PlayersDB> m_playersDB;
};

