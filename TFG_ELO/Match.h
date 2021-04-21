#pragma once
#include "Team.h"

class Match
{
public:
	Match(int i_id);

	inline int getId() {
		return m_id;
	}

	inline vector<shared_ptr<Team>> getTeamsMatch() {
		return m_teamsMatch;
	}

	void addTeamMatch(const shared_ptr<Team>& i_team);

private:
	int m_id;
	vector<shared_ptr<Team>> m_teamsMatch;
};

