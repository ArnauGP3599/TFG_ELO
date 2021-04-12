#include "Precompiled.h"
#include "ExcelExporter.h"

void ExcelExporter::exportToExcel() {
    ofstream myFile;
    myFile.open("Statistics.csv");
    myFile << "ID player;Match;Elo;\n";
    list<vector<int>> statistics = Exporter::m_Statistics->getStatistics();
    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        vector<int> dataPlayer = *it;
        string s;
        for (int i = 0; i < dataPlayer.size(); i++) {
            s += to_string(dataPlayer[i]) + ";";
        }
        s += "\n";
        myFile << s;
    }
    myFile.close();
}