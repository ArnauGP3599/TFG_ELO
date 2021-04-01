#include "Precompiled.h"
#include "Simulation.h"


void Simulation::init() {
    cout << "Introdueix numero de jugadors" << endl;
    cin >> numPlayers;
    cout << "Introdueix numero de jugadors per equip" << endl;
    cin >> numPlayersTeam;
    cout << "Introdueix DeltaElo" << endl;
    cin >> deltaElo;
    shared_ptr<PlayersDB> playersDB = make_shared<PlayersDB>();
    playersDB->init();
    playersDB->addPlayers(numPlayers);
    vector<shared_ptr<Player>> p1 = playersDB->getPlayers();
}