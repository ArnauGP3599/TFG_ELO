#include <iostream>
#include "Precompiled.h"
#include <stdio.h>
#include "Simulation.h"

int main()
{
    int numPlayers, numPlayersTeam, deltaElo, numTotalMatches;
    cout << "Introdueix numero de jugadors" << endl;
    cin >> numPlayers;
    cout << "Introdueix numero de jugadors per equip" << endl;
    cin >> numPlayersTeam;
    cout << "Introdueix DeltaElo" << endl;
    cin >> deltaElo;
    cout << "Introdueix numero de partides" << endl;
    cin >> numTotalMatches;
    Simulation sim = Simulation();
    sim.init(numPlayers, numPlayersTeam, deltaElo, numTotalMatches);
    sim.startSimulation();
}


