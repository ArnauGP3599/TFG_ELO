#include <iostream>
#include "Precompiled.h"
#include <stdio.h>
#include "Simulation.h"

namespace domini
{
    void startProgram(int numPlayers, int numPlayersTeam, int numTeamsMatch, int deltaElo, int numTotalMatches, string path) {
        Simulation sim = Simulation();
        Simulation::InitResult correct = sim.init(numPlayers, numPlayersTeam, numTeamsMatch,deltaElo, numTotalMatches);
        if (correct == Simulation::InitResult::Success) {
            list<vector<int>> statistics = sim.startSimulation();
            ExcelExporter excelExporter = ExcelExporter(path);
            excelExporter.export2(statistics);
        }
    }
}

int main()
{
    int numPlayers, numPlayersTeam, numTeamsMatch, deltaElo, numTotalMatches;
    string path;
    cout << "Introdueix numero de jugadors" << endl;
    cin >> numPlayers;
    cout << "Introdueix numero de jugadors per equip" << endl;
    cin >> numPlayersTeam;
    cout << "Introdueix numero d'equips per partida" << endl;
    cin >> numTeamsMatch;
    cout << "Introdueix DeltaElo" << endl;
    cin >> deltaElo;
    cout << "Introdueix numero de partides" << endl;
    cin >> numTotalMatches;
    cout << "introdueix destinació per a les estadistiques" << endl;
    cin >> path;
    domini::startProgram(numPlayers, numPlayersTeam, numTeamsMatch, deltaElo, numTotalMatches, path);
}




