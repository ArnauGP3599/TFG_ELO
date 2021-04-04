#include "Precompiled.h"
#include "TeamBuilder.h"


TeamBuilder::TeamBuilder() {
}

TeamBuilder::TeamBuilder(int numPlayersTeam, int deltaElo) {
	this->numPlayersTeam = numPlayersTeam;
	this->deltaElo = deltaElo;
}

vector<shared_ptr<Team>> TeamBuilder::createTeams(vector<shared_ptr<Player>>& players) {
	vector<shared_ptr<Team>> teamsC;
	int numTeams = players.size() / numPlayersTeam;
	if (numTeams % 2 != 0) numTeams--;
	int actTeam = 0;
	while (actTeam < numTeams) {
		shared_ptr<Team> t = make_shared<Team>(actTeam);
		int eloSum = 0;
		for (int i = actTeam * numPlayersTeam; i < (actTeam + 1) * numPlayersTeam; i++) {
			t->addPlayerInTeam(players[i]);
			eloSum += players[i]->getElo();
		}
		eloSum = eloSum / numPlayersTeam;
		t->setEloTeam(eloSum);
		teamsC.push_back(t);
		++actTeam;
	}
	return teamsC;
}
