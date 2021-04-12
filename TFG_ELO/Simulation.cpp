#include "Precompiled.h"
#include "Simulation.h"


void Simulation::init(int i_numPlayers, int i_numPlayersTeam, int i_deltaElo, int i_numTotalMatches) {
    m_numPlayers = i_numPlayers;
    m_numPlayersTeam = i_numPlayersTeam;
    m_deltaElo = i_deltaElo;
    m_numTotalMatches = i_numTotalMatches;
    playersDB = make_shared<PlayersDB>();
    playersDB->init();
    playersDB->addPlayers(m_numPlayers);
    teamBuilder = make_shared<TeamBuilder>(m_numPlayersTeam, m_deltaElo);
    matchMaker = make_shared<MatchMaker>(m_deltaElo);
    matchSimulator = make_shared<MatchSimulator>();
    statistics = make_shared<Statistics>();
    statistics->init(playersDB);
    eloCalculator = make_shared<EloCalculator>();
    result = make_shared<Result>();
    result->init(playersDB);
    exporter = make_shared<Exporter>();
    excelExporter = make_shared<ExcelExporter>();
    excelExporter->init(statistics);
}

void Simulation::startSimulation() {
    vector<shared_ptr<Player>> p1 = playersDB->getPlayers();
    cout << p1[0]->getElo() << " " << p1[0]->getNumMatches() << endl;
    cout << p1[6]->getElo() << " " << p1[6]->getNumMatches() << endl;
    cout << endl;
    for (int j = 0; j < m_numTotalMatches; j++) {
        vector<shared_ptr<Team>> teams = teamBuilder->createTeams(p1);
        vector<shared_ptr<Match>> matches = matchMaker->searchMatch(teams);
        for (int i = 0; i < matches.size(); i++) {
            shared_ptr<Classification> classification = matchSimulator->simulateMatch(matches[i]);
            map<int, EloScore> deltaEloTeam = eloCalculator->calculateElo(classification);
            result->changeEloPlayers(deltaEloTeam);
        }
        statistics->updateStatistics();
        cout << p1[0]->getElo() << " " << p1[0]->getNumMatches() << endl;
        cout << p1[6]->getElo() << " " << p1[6]->getNumMatches() << endl;
        cout << endl;
    }
    excelExporter->exportToExcel();
}