#pragma once

#include "Match.h"
#include "Team.h"

class MatchMaker
{
public:
	MatchMaker(int deltaElo);

	vector<shared_ptr<Match>> searchMatch(vector<shared_ptr<Team>>&);

private:
	int deltaElo, idMatch;
};

