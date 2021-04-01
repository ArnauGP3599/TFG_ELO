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
    shared_ptr<MatchMaker> matchMaker = make_shared<MatchMaker>(deltaElo);
    vector<shared_ptr<Match>> matches = matchMaker->searchMatch(teams);
    for (int i = 0; i < matches.size(); i++) {
        cout << "En el partit " << matches[i]->getId() << " juguen els equips :" << endl;
        vector<shared_ptr<Team>> m1 = matches[i]->getTeamsMatch();
        for (int j = 0; j < m1.size(); j++) {
            cout << m1[j]->getId() << " , ";
        }
        cout << endl;
    }
}