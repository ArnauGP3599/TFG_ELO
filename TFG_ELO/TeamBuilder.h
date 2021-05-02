#pragma once
#include "Player.h"
#include "Team.h"
class TeamBuilder
{
public:
	TeamBuilder(int numPlayersTeam, int deltaElo);
	vector<shared_ptr<Team>> createTeams(const vector<shared_ptr<Player>>& players);

private:
	int m_deltaElo;
	int m_numPlayersTeam;

	bool playerFitsTeam(const int eloPlayer, const shared_ptr<Team>& team);
	void modifyIntervalTeam(const int eloPlayer, shared_ptr<Team>& team);
};

