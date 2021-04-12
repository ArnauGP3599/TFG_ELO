#pragma once

#include "Match.h"
#include "Team.h"

class MatchMaker
{
public:
	MatchMaker(int i_deltaElo);

	vector<shared_ptr<Match>> searchMatch(const vector<shared_ptr<Team>>&);

private:
	int m_deltaElo, idMatch;
};

