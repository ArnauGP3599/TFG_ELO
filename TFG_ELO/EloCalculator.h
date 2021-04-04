#pragma once
#include "EloAlgorithm.h"
#include "Classification.h"

class EloCalculator
{
public:
	EloCalculator();
	pair<int, int> calculateElo(shared_ptr<Classification>& classification);
private:
	shared_ptr<EloAlgorithm> eloAlgorithm;
	int k;
};

