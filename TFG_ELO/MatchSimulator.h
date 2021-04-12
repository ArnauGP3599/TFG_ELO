#pragma once

#include "Match.h"
#include "Classification.h"
#include "MatchAlgorithm.h"

class MatchSimulator
{
public:
	MatchSimulator();
	shared_ptr<Classification> simulateMatch(shared_ptr<Match>& match);
private:
	shared_ptr<MatchAlgorithm> matchAlgorithm;
};

