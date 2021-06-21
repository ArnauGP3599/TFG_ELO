#include "Precompiled.h"
#include "Statistics.h"

void Statistics::init(shared_ptr<PlayersDB>& i_playersDB) {
	m_playersDB = i_playersDB;
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (int i = 0; i < players.size(); i++) {
		vector<int> v;
		int elo = players[i]->getElo();
		v.emplace_back(elo);
		m_statistics.emplace_back(v);
	}
}

vector<vector<int>> Statistics::getStatistics() {
	return m_statistics;
}

void Statistics::updateStatistics() {
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (int i = 0; i < players.size(); i++) {
		int id = players[i]->getId();
		m_statistics[id].emplace_back(players[i]->getElo());
	}
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