#include "Precompiled.h"
#include "MatchSimulator.h"

MatchSimulator::MatchSimulator() {
	matchAlgorithm = make_shared<MatchAlgorithm>();
}

shared_ptr<Classification> MatchSimulator::simulateMatch(shared_ptr<Match>& match) {
	shared_ptr<Classification> classification = make_shared<Classification>();
	vector<shared_ptr<Team>> teamsMatch = match->getTeamsMatch();
	vector < shared_ptr<Team>> teamsMatchPosition;
	int res1 = matchAlgorithm->playMatchTeam();
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
	}
	return move(classification);
}