#pragma once

#include "Match.h"
#include "Team.h"

class MatchMaker
{
public:
	MatchMaker(int i_deltaElo);

	void init();

	vector<shared_ptr<Match>> searchMatch(const vector<shared_ptr<Team>>&);

private:
	int m_deltaElo;
	int	m_idMatch;

	bool teamFitsMatch(const int eloTeam, shared_ptr<Match>& match);
	void modifyIntervalMatch(const int eloTeam, shared_ptr<Match>& match);
};

