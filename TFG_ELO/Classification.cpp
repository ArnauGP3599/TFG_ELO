#include "Precompiled.h"
#include "Classification.h"

void Classification::addResult(int position, const vector<shared_ptr<Team>> team) {
	pair<int, vector<shared_ptr<Team>>> p(position, team);
	m_classification.emplace(p);
}
