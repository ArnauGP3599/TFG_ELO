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
    cout << p1[0]->getElo() << endl;
    shared_ptr<TeamBuilder> teamBuilder = make_shared<TeamBuilder>(numPlayersTeam, deltaElo);
    vector<shared_ptr<Team>> teams = teamBuilder->createTeams(p1);
    shared_ptr<MatchMaker> matchMaker = make_shared<MatchMaker>(deltaElo);
    vector<shared_ptr<Match>> matches = matchMaker->searchMatch(teams);
    shared_ptr<MatchSimulator> matchSimulator = make_shared<MatchSimulator>();
    shared_ptr<Statistics> statistics = make_shared<Statistics>();
    shared_ptr<EloCalculator> eloCalculator = make_shared<EloCalculator>();
    shared_ptr<Result> result = make_shared<Result>();
    result->init(playersDB);
    for (int i = 0; i < matches.size(); i++) {
        shared_ptr<Classification> classification = matchSimulator->simulateMatch(matches[i]);
        pair<int, int> deltaEloTeam = eloCalculator->calculateElo(classification);
        result->changeEloPlayers(deltaEloTeam, classification);
    }
    cout << p1[0]->getElo() << endl;
}