#include "Precompiled.h"
#include "ExcelExporter.h"

ExcelExporter::ExcelExporter(const string& i_path){
    Exporter::m_path = i_path;
}

void ExcelExporter::export2(const list<vector<int>>& i_statistics) {
    ofstream myFile;
    myFile.open(/*m_path +*/"Statistics.csv");
    myFile << "ID player;Match;Elo;\n";
    //list<vector<int>> statistics = Exporter::m_statistics->getStatistics();
    for (auto it = i_statistics.begin(); it != i_statistics.end(); ++it) {
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