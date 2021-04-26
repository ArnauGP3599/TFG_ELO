#include "Precompiled.h"
#include "Statistics.h"

void Statistics::init(shared_ptr<PlayersDB>& i_playersDB) {
	m_playersDB = i_playersDB;
	m_round = 0;
	updateStatistics();
	writePlayersProperties();
}

list<vector<int>> Statistics::getStatistics() {
	return m_statistics;
}

void Statistics::updateStatistics() {
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (int i = 0; i < players.size(); i++) {
		vector<int> statsPlayer;
		statsPlayer.emplace_back(players[i]->getId());
		statsPlayer.emplace_back(m_round);
		statsPlayer.emplace_back(players[i]->getElo());
		m_statistics.emplace_back(statsPlayer);
	}
	m_round++;
}

void Statistics::writePlayersProperties() {
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (int i = 0; i < players.size(); i++) {
		map<string, int> playersProperties = players[i]->getProperties();
		cout << "El jugador " << players[i]->getId() << " te les propietats: ";
		for (auto it = playersProperties.begin(); it != playersProperties.end(); ++it) {
			cout << it->first << " amb valor " << it->second << ", ";
		}
		cout << endl;
	}
}