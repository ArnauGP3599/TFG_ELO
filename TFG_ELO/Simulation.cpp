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
    shared_ptr<TeamBuilder> teamBuilder = make_shared<TeamBuilder>(numPlayersTeam, deltaElo);
    vector<shared_ptr<Team>> teams = teamBuilder->createTeams(p1);
    for (int i = 0; i < teams.size(); i++) {
        cout << "Soc el team " << teams[i]->getId() << " i tinc com a jugadors: " << endl;
        vector<shared_ptr<Player>> p2 = teams[i]->getPlayersTeam();
        for (int j = 0; j < p2.size(); j++) {
            cout << p2[j]->getId() << " , ";
        }
        cout << endl;
        cout << "El meu elo es de " << teams[i]->getEloTeam() << endl;
    }
}