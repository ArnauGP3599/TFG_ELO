#pragma once
#include <iostream>
#include <stdio.h>
#include "Simulation.h"

namespace domini {
	class TFG_ELO {
	public:
		void startProgram(int numPlayers, int numPlayersTeam, int numTeamsMatch, int deltaElo, int numTotalMatches, string path);
	};
}
