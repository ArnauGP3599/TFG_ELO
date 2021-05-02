#include "Precompiled.h"
#include "Match.h"

Match::Match(int i_id) {
	m_id = i_id;
}

void Match::addTeamMatch(const shared_ptr<Team>& i_team) {
	m_teamsMatch.emplace_back(i_team);
}

int Match::getNumTeamsMatch() {
	return m_teamsMatch.size();
}