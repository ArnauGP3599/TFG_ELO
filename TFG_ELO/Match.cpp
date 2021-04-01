#include "Precompiled.h"
#include "Match.h"

Match::Match(int id) {
	this->id = id;
}

void Match::addTeamMatch(shared_ptr<Team>& team) {
	teamsMatch.push_back(team);
}