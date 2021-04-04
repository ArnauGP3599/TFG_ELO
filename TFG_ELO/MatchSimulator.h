#pragma once

#include "Match.h"
#include "Classification.h"

class MatchSimulator
{
public:
	shared_ptr<Classification> simulateMatch(shared_ptr<Match>& match);
};

