#include "Precompiled.h"
#include "EloCalculator.h"

EloCalculator::EloCalculator() {
	eloAlgorithm = make_shared<EloAlgorithm>();
	k = 20;
 }

pair<int, int> EloCalculator::calculateElo(shared_ptr<Classification>& classification) {
	list<pair<int, shared_ptr<Team>>> classif = classification->getClasification();
	bool first = true;
	int eloTeamA, eloTeamB;
	int deltaEloA, deltaEloB;
	int result;
	for (auto it = classif.begin(); it != classif.end(); ++it) {
		if (first) {
			result = it->first;
			eloTeamA = it->second->getEloTeam();
			first = false;
		}
		else {
			eloTeamB = it->second->getEloTeam();
		}
	}
	if (result == 0) {
		int eloA = k/2 * (1-eloAlgorithm->getExpectedScore(eloTeamA, eloTeamB));
		int eloB = k/2 * (1-eloAlgorithm->getExpectedScore(eloTeamB, eloTeamA));
		deltaEloA = eloA - eloB;
		deltaEloB = eloB - eloA;
	}
	else {
		deltaEloA = k * (1 - eloAlgorithm->getExpectedScore(eloTeamA, eloTeamB));
		deltaEloB = -deltaEloA;
	}
	pair <int, int> deltaEloTeams;
	deltaEloTeams.first = deltaEloA;
	deltaEloTeams.second = deltaEloB;
	return deltaEloTeams;
}

