#pragma once
#include "Team.h"

class Match
{
public:
	Match(int id);

	inline int getId() {
		return id;
	}

	inline vector<shared_ptr<Team>> getTeamsMatch() {
		return teamsMatch;
	}

	void addTeamMatch(shared_ptr<Team>& team);

private:
	int id;
	vector<shared_ptr<Team>> teamsMatch;
};

