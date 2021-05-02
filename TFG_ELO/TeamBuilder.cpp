#include "Precompiled.h"
#include "TeamBuilder.h"


TeamBuilder::TeamBuilder(int i_numPlayersTeam, int i_deltaElo) {
	m_numPlayersTeam = i_numPlayersTeam;
	m_deltaElo = i_deltaElo;
}

bool TeamBuilder::playerFitsTeam(const int eloPlayer, const shared_ptr<Team>& team) {
	int minValue = team->getMinValue();
	int maxValue = team->getMaxValue();
	if (eloPlayer >= minValue and eloPlayer <= maxValue) return true;
	return false;
}

void TeamBuilder::modifyIntervalTeam(const int eloPlayer, shared_ptr<Team>& team) {
	int eloFirstPlayer = team->getEloFirstPlayer();
	if (eloPlayer > eloFirstPlayer) {
		int minValue = team->getMinValue();
		if ((eloPlayer - m_deltaElo) > minValue) {
			minValue = eloPlayer - m_deltaElo;
			team->setMinValue(minValue);
		}
	}
	else if (eloPlayer < eloFirstPlayer) {
		int maxValue = team->getMaxValue();
		if ((eloPlayer + m_deltaElo) < maxValue) {
			maxValue = eloPlayer + m_deltaElo;
			team->setMaxValue(maxValue);
		}
	}
}

vector<shared_ptr<Team>> TeamBuilder::createTeams(const vector<shared_ptr<Player>>& players) {
	vector<shared_ptr<Team>> teamsDone;
	vector<shared_ptr<Team>> teamsCreation;
	for (int i = 0; i < players.size(); i++) {
		int j = 0;
		bool playerPlaced = false;
		int eloPlayer = players[i]->getElo();
		while (j < teamsCreation.size() and !playerPlaced) {
			if (playerFitsTeam(eloPlayer, teamsCreation[j])) {
				playerPlaced = true;
				teamsCreation[j]->addPlayerInTeam(players[i]);
				teamsCreation[j]->addEloTeam(eloPlayer);
				modifyIntervalTeam(eloPlayer, teamsCreation[j]);
				if (m_numPlayersTeam == teamsCreation[j]->getNumPlayersTeam()) {
					teamsCreation[j]->setId(teamsDone.size());
					teamsDone.emplace_back(teamsCreation[j]);
					teamsCreation.erase(teamsCreation.begin() + j);
				}
			}
			j++;
		}
		if (!playerPlaced) {
			shared_ptr<Team> t = make_shared<Team>(1);
			t->addPlayerInTeam(players[i]);
			t->addEloTeam(eloPlayer);
			t->setEloFirstPlayer(eloPlayer);
			if (m_numPlayersTeam == t->getNumPlayersTeam()) {
				t->setId(teamsDone.size());
				teamsDone.emplace_back(t);
			}
			else {
				teamsCreation.emplace_back(t);
				t->setMinValue(eloPlayer - m_deltaElo);
				t->setMaxValue(eloPlayer + m_deltaElo);
			}
		}
	}
	/*for (int i = 0; i < teamsDone.size(); i++) {
		cout << "-------------teamsDone------------------" << endl;
		cout << "Team " << teamsDone[i]->getId() << endl;
		vector<shared_ptr<Player>> p = teamsDone[i]->getPlayersTeam();
		for (int j = 0; j < p.size(); j++) {
			cout << "Player ID " << p[j]->getId() << " amb elo " << p[j]->getElo() << endl;
		}
	}

	for (int i = 0; i < teamsCreation.size(); i++) {
		cout << "-------------teamsCreation------------------" << endl;
		cout << "Team " << teamsCreation[i]->getId() << endl;
		vector<shared_ptr<Player>> p = teamsCreation[i]->getPlayersTeam();
		for (int j = 0; j < p.size(); j++) {
			cout << "Player ID " << p[j]->getId() << " amb elo " << p[j]->getElo() << endl;
		}
	}*/
	return move(teamsDone);
}
