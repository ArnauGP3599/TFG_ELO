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
	int round;
	list<vector<int>> statistics;
	shared_ptr<PlayersDB> m_playersDB;
};

