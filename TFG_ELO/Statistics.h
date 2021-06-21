#pragma once

#include <list>
#include "PlayersDB.h"

class Statistics
{
public:
	void init(shared_ptr<PlayersDB>& i_playersDB);
	void updateStatistics();

	vector<vector<int>> getStatistics();

private:
	void writePlayersProperties();
	vector<vector<int>> m_statistics;
	shared_ptr<PlayersDB> m_playersDB;
};

