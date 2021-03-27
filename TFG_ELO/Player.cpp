#include "Player.h"

void Player::createPlayers(int numPlayers) {
	for (int i = 0; i < numPlayers; i++) {
		addPlayer(i);
	}
}

void Player::addPlayer(int id) {
	player p = player();
	p.id = id;
	p.elo = rand()%1501;
	p.numMatches = 0;
	players.push_back(p);
}
