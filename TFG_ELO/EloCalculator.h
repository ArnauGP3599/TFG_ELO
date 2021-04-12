#pragma once
#include "EloAlgorithm.h"
#include "Classification.h"

class EloCalculator
{
public:
	EloCalculator();
	map <int, EloScore> calculateElo(shared_ptr<Classification>& classification);
private:
	void addPlayersMap(vector<shared_ptr<Player>>& playersTeam, int deltaEloTeam);

	map<int, EloScore> deltaEloTeams;
	shared_ptr<EloAlgorithm> eloAlgorithm;
	int k;
};

