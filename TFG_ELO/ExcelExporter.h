#pragma once

#include "Exporter.h"
#include <fstream>
#include <list>
#include <iterator>

class ExcelExporter : public Exporter
{
public:
	//void exportToExcel();
	ExcelExporter(const string& i_path);
	void export2(const list<vector<int>>& i_statistics);
};

