#include "TeamBuilder.h"

TeamBuilder::TeamBuilder() {
	teamC = make_shared<Team>();
	teamsMade.clear();
}

void TeamBuilder::makeTeams(const vector<Player::player>& players) {
	teamC->setTeams(teamsMade);
}
