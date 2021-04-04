#include "Precompiled.h"
#include "Result.h"

void Result::init(shared_ptr<PlayersDB>& playersDB) {
	this->playersDB = playersDB;
}

void Result::changeEloPlayers(pair<int, int> eloChange, shared_ptr<Classification>& classification) {
	list<pair<int, shared_ptr<Team>>> classif = classification->getClasification();
	vector<shared_ptr<Player>> players = playersDB->getPlayers();
	bool first = true;
	for (auto it = classif.begin(); it != classif.end(); it++) {
		vector<shared_ptr<Player>> playersTeam = it->second->getPlayersTeam();
		int deltaElo;
		if (first) deltaElo = eloChange.first;
		else deltaElo = eloChange.second;
		for (int i = 0; i < playersTeam.size(); i++) {
			int idPlayer = playersTeam[i]->getId();
			int eloPlayer = playersTeam[i]->getElo();
			int numMatchesPlayer = playersTeam[i]->getNumMatches();
			players[idPlayer]->setElo(eloPlayer + deltaElo);
			players[idPlayer]->setNumMatches(numMatchesPlayer+1);
		}
		first = false;
	}
}