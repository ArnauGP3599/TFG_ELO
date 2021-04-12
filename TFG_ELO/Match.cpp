#include "Precompiled.h"
#include "Match.h"

Match::Match(int i_id) {
	m_id = i_id;
}

void Match::addTeamMatch(shared_ptr<Team>& team) {
	teamsMatch.emplace_back(team);
}