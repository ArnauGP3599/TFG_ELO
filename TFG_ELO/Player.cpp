#include"Precompiled.h"
#include "Player.h"


Player::Player() {
}

Player::Player(int i_id) {
	m_id = i_id;
	m_elo = rand() % 1501;
	m_numMatches = 0;
}
