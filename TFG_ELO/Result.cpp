#include "Precompiled.h"
#include "Result.h"

void Result::init(shared_ptr<PlayersDB>& i_playersDB) {
	m_playersDB = i_playersDB;
}

void Result::changeEloPlayers(const map<int, EloScore> eloChange) {
	vector<shared_ptr<Player>> players = m_playersDB->getPlayers();
	for (auto it = eloChange.begin(); it != eloChange.end(); it++) {
		int eloPlayer = players[it->first]->getElo();
		int numMatchesPlayer = players[it->first]->getNumMatches();
		int elo = eloPlayer + it->second;
		if (elo < 0) elo = 0;
		players[it->first]->setElo(elo);
		players[it->first]->setNumMatches(numMatchesPlayer+1);
	}
}