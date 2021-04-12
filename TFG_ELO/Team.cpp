#include "Precompiled.h"
#include "Team.h"

Team::Team(int i_id) {
	m_id = i_id;
	m_eloTeam = 0;
}

void Team::addPlayerInTeam(shared_ptr<Player>& player) {
	playersTeam.emplace_back(player);
}

