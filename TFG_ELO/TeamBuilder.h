#pragma once
#include "Precompiled.h"
#include "Player.h"
#include "Team.h"
class TeamBuilder
{
public:
	TeamBuilder();
	void makeTeams(const vector<Player::player>& players);

private:
	vector<Team::team> teamsMade;
	shared_ptr<Team> teamC;
};

