#pragma once

#include "Match.h"
#include "Classification.h"
#include "MatchAlgorithm.h"

class MatchSimulator
{
public:
	MatchSimulator(lua_State * i_L);
	shared_ptr<Classification> simulateMatch(shared_ptr<Match>& match);
	//void ferprova();
private:
	shared_ptr<MatchAlgorithm> matchAlgorithm;
};

