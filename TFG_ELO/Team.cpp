#include "Precompiled.h"
#include "Team.h"

Team::Team(int id) {
	this->id = id;
	this->eloTeam = 0;
}

void Team::addPlayerInTeam(shared_ptr<Player>& player) {
	playersTeam.push_back(player);
}

