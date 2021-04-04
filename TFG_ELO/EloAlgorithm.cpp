#include "Precompiled.h"
#include "EloAlgorithm.h"

double EloAlgorithm::getExpectedScore(int teamA, int teamB) {
	float deltaTeam = teamB - teamA;
	float divElev = deltaTeam / 800.f;
	float elev = pow(10.f, divElev);
	return (1.f / (1.f + elev));
}
