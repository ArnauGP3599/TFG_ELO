#include "Precompiled.h"
#include "Simulation.h"


void Simulation::init(int i_numPlayers, int i_numPlayersTeam, int i_deltaElo, int i_numTotalMatches) {
    m_numPlayers = i_numPlayers;
    m_numPlayersTeam = i_numPlayersTeam;
    m_deltaElo = i_deltaElo;
    m_numTotalMatches = i_numTotalMatches;
    m_playersDB = make_shared<PlayersDB>();
    m_playersDB->init();
    m_playersDB->addPlayers(m_numPlayers);
    m_teamBuilder = make_shared<TeamBuilder>(m_numPlayersTeam, m_deltaElo);
    m_matchMaker = make_shared<MatchMaker>(m_deltaElo);
    m_matchSimulator = make_shared<MatchSimulator>();
    m_statistics = make_shared<Statistics>();
    m_statistics->init(m_playersDB);
    m_eloCalculator = make_shared<EloCalculator>();
    m_result = make_shared<Result>();
    m_result->init(m_playersDB);
    //excelExporter = make_shared<ExcelExporter>();
    //excelExporter->init(statistics);
}

list<vector<int>> Simulation::startSimulation() {
    vector<shared_ptr<Player>> p1 = m_playersDB->getPlayers();
    for (int j = 0; j < m_numTotalMatches; j++) {
        vector<shared_ptr<Team>> teams = m_teamBuilder->createTeams(p1);
        vector<shared_ptr<Match>> matches = m_matchMaker->searchMatch(teams);
        for (int i = 0; i < matches.size(); i++) {
            shared_ptr<Classification> classification = m_matchSimulator->simulateMatch(matches[i]);
            map<int, EloScore> deltaEloTeam = m_eloCalculator->calculateElo(classification);
            m_result->changeEloPlayers(deltaEloTeam);
        }
        m_statistics->updateStatistics();
    }
    //excelExporter->exportToExcel();
    return m_statistics->getStatistics();
}