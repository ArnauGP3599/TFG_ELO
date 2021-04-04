#include "Precompiled.h"
#include "Simulation.h"


void Simulation::init(int numPlayers, int numPlayersTeam, int deltaElo, int numTotalMatches) {
    this->numPlayers = numPlayers;
    this->numPlayersTeam = numPlayersTeam;
    this->deltaElo = deltaElo;
    this->numTotalMatches = numTotalMatches;
    playersDB = make_shared<PlayersDB>();
    playersDB->init();
    playersDB->addPlayers(numPlayers);
    teamBuilder = make_shared<TeamBuilder>(numPlayersTeam, deltaElo);
    matchMaker = make_shared<MatchMaker>(deltaElo);
    matchSimulator = make_shared<MatchSimulator>();
    statistics = make_shared<Statistics>();
    eloCalculator = make_shared<EloCalculator>();
    result = make_shared<Result>();
    result->init(playersDB);
    
}

void Simulation::startSimulation() {
    vector<shared_ptr<Player>> p1 = playersDB->getPlayers();
    cout << p1[0]->getElo() << " " << p1[0]->getNumMatches() << endl;
    cout << p1[6]->getElo() << " " << p1[6]->getNumMatches() << endl;
    cout << endl;
    for (int j = 0; j < numTotalMatches; j++) {
        vector<shared_ptr<Team>> teams = teamBuilder->createTeams(p1);
        vector<shared_ptr<Match>> matches = matchMaker->searchMatch(teams);
        for (int i = 0; i < matches.size(); i++) {
            shared_ptr<Classification> classification = matchSimulator->simulateMatch(matches[i]);
            pair<int, int> deltaEloTeam = eloCalculator->calculateElo(classification);
            result->changeEloPlayers(deltaEloTeam, classification);
        }
        cout << p1[0]->getElo() << " " << p1[0]->getNumMatches() << endl;
        cout << p1[6]->getElo() << " " << p1[6]->getNumMatches() << endl;
        cout << endl;
    }
}