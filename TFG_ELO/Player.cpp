#include"Precompiled.h"
#include "Player.h"


Player::Player(int i_id) {
	m_id = i_id;
	m_elo = rand() % 1501;
	m_numMatches = 0;
}

void Player::addProperty(const string i_name, const int i_value) {
	m_properties.emplace(i_name, i_value);
}