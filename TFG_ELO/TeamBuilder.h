#pragma once
#include "Player.h"
#include "Team.h"
class TeamBuilder
{
public:
	TeamBuilder();
	TeamBuilder(int numPlayersTeam, int deltaElo);
	vector<shared_ptr<Team>> createTeams(vector<shared_ptr<Player>>& players);

private:
	int deltaElo, numPlayersTeam;
};

