#include "Precompiled.h"
#include "MatchMaker.h"

MatchMaker::MatchMaker(int i_deltaElo, int i_numTeamsMatch) {
	m_deltaElo = i_deltaElo;
	m_numTeamsMatch = i_numTeamsMatch;
}

void MatchMaker::init() {
	m_idMatch = 0;
}

bool MatchMaker::teamFitsMatch(const int eloTeam, shared_ptr<Match>& match) {
	int minValue = match->getMinValue();
	int maxValue = match->getMaxValue();
	if (eloTeam >= minValue and eloTeam <= maxValue) return true;
	return false;
}

void MatchMaker::modifyIntervalMatch(const int eloTeam, shared_ptr<Match>& match) {
	int eloFirstTeam = match->getEloFirstTeam();
	if (eloTeam > eloFirstTeam) {
		int minValue = match->getMinValue();
		if ((eloTeam - m_deltaElo) > minValue) {
			minValue = eloTeam - m_deltaElo;
			match->setMinValue(minValue);
		}
	}
	else if (eloTeam < eloFirstTeam) {
		int maxValue = match->getMaxValue();
		if ((eloTeam + m_deltaElo) < maxValue) {
			maxValue = eloTeam + m_deltaElo;
			match->setMaxValue(maxValue);
		}
	}
}

vector<shared_ptr<Match>> MatchMaker::searchMatch(const vector < shared_ptr<Team>>& teams) {
	vector<shared_ptr<Match>> matchesPrepared;
	vector<shared_ptr<Match>> matchesCreation;
	//cout << "--------------------------New Round-------------------------------" << endl;
	for (int i = 0; i < teams.size(); i++) {
		int j = 0;
		bool teamPlaced = false;
		int eloTeam = teams[i]->getEloTeam();
		while (j < matchesCreation.size() and !teamPlaced) {
			if (teamFitsMatch(eloTeam, matchesCreation[j])) {
				teamPlaced = true;
				matchesCreation[j]->addTeamMatch(teams[i]);
				modifyIntervalMatch(eloTeam, matchesCreation[j]);
				if (m_numTeamsMatch == matchesCreation[j]->getNumTeamsMatch()) {
					matchesCreation[j]->setId(m_idMatch);
					matchesPrepared.emplace_back(matchesCreation[j]);
					matchesCreation.erase(matchesCreation.begin() + j);
					++m_idMatch;
				}
			}
			j++;
		}
		if (!teamPlaced) {
			shared_ptr<Match> m = make_shared<Match>(1);
			m->addTeamMatch(teams[i]);
			m->setMinValue(eloTeam - m_deltaElo);
			m->setMaxValue(eloTeam + m_deltaElo);
			matchesCreation.emplace_back(m);
		}
	}

	/*for (int i = 0; i < matchesPrepared.size(); i++) {
		cout << "-------------matchesPrepared------------------" << endl;
		cout << "Match " << matchesPrepared[i]->getId() << endl;
		vector<shared_ptr<Team>> p = matchesPrepared[i]->getTeamsMatch();
		for (int j = 0; j < p.size(); j++) {
			cout << "Team ID " << p[j]->getId() << " amb elo " << p[j]->getEloTeam() << endl;
		}
	}

	for (int i = 0; i < matchesCreation.size(); i++) {
		cout << "-------------matchesCreation------------------" << endl;
		cout << "Match " << matchesCreation[i]->getId() << endl;
		vector<shared_ptr<Team>> p = matchesCreation[i]->getTeamsMatch();
		for (int j = 0; j < p.size(); j++) {
			cout << "Team ID " << p[j]->getId() << " amb elo " << p[j]->getEloTeam() << endl;
		}
	}*/
	
	/*int numMatches = teams.size() / 2;
	for (int i = 0; i < numMatches; i++) {
		shared_ptr<Match> m = make_shared<Match>(m_idMatch);
		for (int j = i * 2; j < (i + 1) * 2; j++){
			m->addTeamMatch(teams[j]);
		}
		matches.emplace_back(m);
		m_idMatch++;
	}*/
	return move(matchesPrepared);
}

