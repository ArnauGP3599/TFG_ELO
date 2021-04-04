#include "Precompiled.h"
#include "Classification.h"

void Classification::addResult(int position, shared_ptr<Team> team) {
	pair<int, shared_ptr<Team>> p(position, team);
	classification.push_back(p);
}
