#pragma once

#include "Team.h"
#include <map>
#include <iterator>

class Classification
{
public:
	void addResult(int position, vector<shared_ptr<Team>> team);
	inline map<int, vector<shared_ptr<Team>>> getClasification() {
		return classification;
	}
private:
	map<int, vector<shared_ptr<Team>>> classification;
};

