#pragma once

#include "Statistics.h"

class Exporter
{
public:
	virtual void export2(const vector<vector<int>>& i_statistics) = 0;
	
/*public:
	void init(shared_ptr<Statistics>& i_Statistics);
*/
protected:
	string m_path;
};

