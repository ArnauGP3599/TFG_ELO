#include "Precompiled.h"
#include "ExcelExporter.h"

ExcelExporter::ExcelExporter(const string& i_path){
    Exporter::m_path = i_path;
}

void ExcelExporter::export2(const vector<vector<int>>& i_statistics) {
    ofstream myFile;
    myFile.open(m_path + "/Statistics.csv");
    int size = 0;
    if (i_statistics.size() > 0) {
        size += i_statistics[0].size();
    }
    string headers = "ID player";
    for (int i = 0; i < size; i++) {
        headers += "; Round " + to_string(i);
    }
    headers += "\n";
    myFile << headers;
    //list<vector<int>> statistics = Exporter::m_statistics->getStatistics();

    for (int i = 0; i < i_statistics.size(); i++) {
        string s = to_string(i) + ";";
        for (int j = 0; j < i_statistics[i].size(); j++) {
            s += to_string(i_statistics[i][j]) + ";";
        }
        s += "\n";
        myFile << s;
    }
    myFile.close();
}