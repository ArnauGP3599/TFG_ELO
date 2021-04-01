#include "Precompiled.h"
#include "PlayersDB.h"

void PlayersDB::init() {
	players.clear();
}

void PlayersDB::addPlayers(int numPlayers) {
	for (int i = 0; i < numPlayers; i++) {
		shared_ptr<Player> p = make_shared<Player>(i);
		players.push_back(p);
	}
}

vector<shared_ptr<Player>> PlayersDB::getPlayers() {
	return players;
}
