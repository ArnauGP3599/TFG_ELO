#pragma once
#include "Player.h"
#include "Team.h"
class TeamBuilder
{
public:
	TeamBuilder();
	TeamBuilder(int numPlayersTeam, int deltaElo);
	vector<shared_ptr<Team>> createTeams(const vector<shared_ptr<Player>>& players);

private:
	int m_deltaElo;
	int m_numPlayersTeam;
};

