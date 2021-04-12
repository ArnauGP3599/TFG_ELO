#include "Precompiled.h"
#include "TeamBuilder.h"


TeamBuilder::TeamBuilder() {
}

TeamBuilder::TeamBuilder(int i_numPlayersTeam, int i_deltaElo) {
	m_numPlayersTeam = i_numPlayersTeam;
	m_deltaElo = i_deltaElo;
}

vector<shared_ptr<Team>> TeamBuilder::createTeams(vector<shared_ptr<Player>>& players) {
	vector<shared_ptr<Team>> teamsC;
	int numTeams = players.size() / m_numPlayersTeam;
	if (numTeams % 2 != 0) numTeams--;
	int actTeam = 0;
	while (actTeam < numTeams) {
		shared_ptr<Team> t = make_shared<Team>(actTeam);
		int eloSum = 0;
		for (int i = actTeam * m_numPlayersTeam; i < (actTeam + 1) * m_numPlayersTeam; i++) {
			t->addPlayerInTeam(players[i]);
			eloSum += players[i]->getElo();
		}
		eloSum = eloSum / m_numPlayersTeam;
		t->setEloTeam(eloSum);
		teamsC.emplace_back(t);
		++actTeam;
	}
	return move(teamsC);
}
