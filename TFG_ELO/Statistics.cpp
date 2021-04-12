#include "Precompiled.h"
#include "Statistics.h"

void Statistics::init(shared_ptr<PlayersDB>& i_playersDB) {
	m_playersDB = i_playersDB;
	round = 0;
	updateStatistics();
}

list<vector<int>> Statistics::getStatistics() {
	return statistics;
}

void Statistics::updateStatistics() {
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (int i = 0; i < players.size(); i++) {
		vector<int> statsPlayer;
		statsPlayer.emplace_back(players[i]->getId());
		statsPlayer.emplace_back(round);
		statsPlayer.emplace_back(players[i]->getElo());
		statistics.emplace_back(statsPlayer);
	}
	round++;
}

