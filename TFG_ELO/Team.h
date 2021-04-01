#pragma once
#include "Player.h"

class Team
{
	public:
		struct team{
			int id;
			vector<Player> playersTeam;
			int eloTeam;
		};
		inline void setTeams(vector<team> teamsMaked) {
			teams = teamsMaked;
		}
	
	private:
		vector<team> teams;
};

