#include "Precompiled.h"
#include "EloCalculator.h"

EloCalculator::EloCalculator(lua_State* i_L) {
	m_eloAlgorithm = make_shared<EloAlgorithm>(i_L);
	k = 20;
 }

map <int, EloScore> EloCalculator::calculateElo(shared_ptr<Classification>& classification) {
	/*map<int, vector<shared_ptr<Team>>> classif = classification->getClasification();
	bool first = true;
	bool draw = false;
	int eloTeamA, eloTeamB;
	m_deltaEloTeams.clear();
	vector<shared_ptr<Team>> teamClassification;
	vector<shared_ptr<Player>> playersTeamA;
	vector<shared_ptr<Player>> playersTeamB;
	int deltaEloA, deltaEloB;
	for (auto it = classif.begin(); it != classif.end(); ++it) {
		teamClassification = it->second;
		if (teamClassification.size() > 1) {
			draw = true;
		}
		for (int i = 0; i < teamClassification.size(); i++) {
			if (first) {
				eloTeamA = teamClassification[i]->getEloTeam();
				playersTeamA = teamClassification[i]->getPlayersTeam();
				first = false;
			}
			else {
				eloTeamB = teamClassification[i]->getEloTeam();
				playersTeamB = teamClassification[i]->getPlayersTeam();
			}
		}
	}
	//cout << "A " << eloTeamA << " - B " << eloTeamB << endl;
	if (draw) {
		int eloA = k/2 * (1-m_eloAlgorithm->getExpectedScore(eloTeamA, eloTeamB));
		int eloB = k/2 * (1-m_eloAlgorithm->getExpectedScore(eloTeamB, eloTeamA));
		deltaEloA = eloA - eloB;
		deltaEloB = eloB - eloA;
	}
	else {
		deltaEloA = k * (1 - m_eloAlgorithm->getExpectedScore(eloTeamA, eloTeamB));
		deltaEloB = -deltaEloA;
	}
	//cout << "dA " << deltaEloA << " - dB " << deltaEloB << endl;
	addPlayersMap(playersTeamA, deltaEloA);
	addPlayersMap(playersTeamB, deltaEloB);
	return m_deltaEloTeams;*/
	return m_eloAlgorithm->calculateEloScore(classification);
}

void EloCalculator::addPlayersMap(const vector<shared_ptr<Player>>& playersTeam, int deltaEloTeam) {
	for (int i = 0; i < playersTeam.size(); i++) {
		int idPlayer = playersTeam[i]->getId();
		pair<int, EloScore> p(idPlayer, deltaEloTeam);
		m_deltaEloTeams.emplace(p);
	}
}

