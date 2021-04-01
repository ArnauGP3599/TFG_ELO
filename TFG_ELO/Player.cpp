#include"Precompiled.h"
#include "Player.h"


Player::Player() {
}

Player::Player(int id) {
	this->id = id;
	this->elo = rand() % 1501;
	this->numMatches = 0;
}
