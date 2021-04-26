#pragma once
#include "EloAlgorithm.h"
#include "Classification.h"

class EloCalculator
{
public:
	EloCalculator(lua_State* i_L);
	map <int, EloScore> calculateElo(shared_ptr<Classification>& classification);
private:
	void addPlayersMap(const vector<shared_ptr<Player>>& playersTeam, int deltaEloTeam);

	map<int, EloScore> m_deltaEloTeams;
	shared_ptr<EloAlgorithm> m_eloAlgorithm;
	int k;
};

