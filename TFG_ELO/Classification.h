#pragma once

#include "Team.h"
#include <map>
#include <iterator>

class Classification
{
public:
	void addResult(int position, const vector<shared_ptr<Team>> team);
	inline map<int, vector<shared_ptr<Team>>> getClasification() {
		return m_classification;
	}
private:
	map<int, vector<shared_ptr<Team>>> m_classification;
};

