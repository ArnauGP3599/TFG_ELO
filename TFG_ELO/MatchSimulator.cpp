#include "Precompiled.h"
#include "MatchSimulator.h"

shared_ptr<Classification> MatchSimulator::simulateMatch(shared_ptr<Match>& match) {
	shared_ptr<Classification> classification = make_shared<Classification>();
	vector<shared_ptr<Team>> teamsMatch = match->getTeamsMatch();
	int res1 = rand() % 100;
	int res2 = rand() % 100;
	if (res1 == res2) {
		classification->addResult(0, teamsMatch[0]);
		classification->addResult(0, teamsMatch[1]);
	}
	else if (res1 < res2) {
		classification->addResult(1, teamsMatch[1]);
		classification->addResult(2, teamsMatch[0]);
	}
	else {
		classification->addResult(1, teamsMatch[0]);
		classification->addResult(2, teamsMatch[1]);
	}
	return classification;
}