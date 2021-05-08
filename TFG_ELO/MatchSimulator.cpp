#include "Precompiled.h"
#include "MatchSimulator.h"

MatchSimulator::MatchSimulator(lua_State* i_L) {
	matchAlgorithm = make_shared<MatchAlgorithm>(i_L);
}

shared_ptr<Classification> MatchSimulator::simulateMatch(shared_ptr<Match>& match) {
	shared_ptr<Classification> classification = make_shared<Classification>();
	vector<shared_ptr<Team>> teamsMatch = match->getTeamsMatch();
	vector < shared_ptr<Team>> teamsMatchPosition;
	matchAlgorithm->playMatch(match);
	vector<int> clasMatch = matchAlgorithm->getResults();

	for (int i = 0; i < clasMatch.size(); i++) {
		//cout << "PosTeam " << clasMatch[i] << endl;
		int posTeam = clasMatch[i] - 1;
		teamsMatchPosition.clear();
		teamsMatchPosition.emplace_back(teamsMatch[posTeam]);
		classification->addResult(i+1, teamsMatchPosition);
	}

	/*int res1 = matchAlgorithm->playMatchTeam();
	int res2 = matchAlgorithm->playMatchTeam();

	if (res1 == res2) {
		teamsMatchPosition.emplace_back(teamsMatch[0]);
		teamsMatchPosition.emplace_back(teamsMatch[1]);
		classification->addResult(1, teamsMatchPosition);
	}
	else if (res1 < res2) {
		teamsMatchPosition.emplace_back(teamsMatch[1]);
		classification->addResult(1, teamsMatchPosition);
		teamsMatchPosition.clear();
		teamsMatchPosition.emplace_back(teamsMatch[0]);
		classification->addResult(2, teamsMatchPosition);
	}
	else {
		teamsMatchPosition.emplace_back(teamsMatch[0]);
		classification->addResult(1, teamsMatchPosition);
		teamsMatchPosition.clear();
		teamsMatchPosition.emplace_back(teamsMatch[1]);
		classification->addResult(2, teamsMatchPosition);
	}*/
	return move(classification);
}