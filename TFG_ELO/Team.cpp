#include "Precompiled.h"
#include "Team.h"

Team::Team(int i_id) {
	m_id = i_id;
	m_eloTeam = 0;
	m_eloTotalTeam = 0;
	m_maxValue = 0;
	m_minValue = 0;
}

void Team::addPlayerInTeam(const shared_ptr<Player>& player) {
	m_playersTeam.emplace_back(player);
}

int Team::getNumPlayersTeam() {
	return m_playersTeam.size();
}

void Team::addEloTeam(int i_elo){
	m_eloTotalTeam += i_elo;
	m_eloTeam = m_eloTotalTeam / m_playersTeam.size();
}
