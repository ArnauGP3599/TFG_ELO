#pragma once

#include "Exporter.h"
#include <fstream>
#include <list>
#include <iterator>

class ExcelExporter : public Exporter
{
public:
	void exportToExcel();
};

