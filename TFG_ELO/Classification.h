#pragma once

#include "Team.h"
#include <list>
#include <iterator>

class Classification
{
public:
	void addResult(int position, shared_ptr<Team> team);
	inline list<pair<int, shared_ptr<Team>>> getClasification() {
		return classification;
	}
private:
	list<pair<int, shared_ptr<Team>>> classification;
};

