#pragma once

#include "Statistics.h"

class Exporter
{
public:
	void init(shared_ptr<Statistics>& i_Statistics);

protected:
	shared_ptr<Statistics> m_Statistics;
};

