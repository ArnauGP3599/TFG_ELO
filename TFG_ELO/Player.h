#pragma once

#include"Precompiled.h"
#include <stdlib.h>  

class Player
{
	public:
		struct player {
			int id;
			int elo;
			int numMatches;
		};
		void createPlayers(int numPlayers);

		inline player getPlayer(int id) {
			return players[id];
		}

	private:
		void addPlayer(int id);

		vector<player> players;
		
};

