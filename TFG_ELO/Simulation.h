#pragma once
#include "PlayersDB.h"
#include "Player.h"
#include "TeamBuilder.h"
#include "MatchMaker.h"
#include "MatchSimulator.h"
#include "Classification.h"
#include "Statistics.h"
#include "EloCalculator.h"
#include "Result.h"
#include "ExcelExporter.h"

class Simulation
{
public:
    void init(int i_numPlayers, int i_numPlayersTeam, int i_deltaElo, int i_numTotalMatches);
    list<vector<int>> startSimulation();

    inline int getNumPlayers() {
        return m_numPlayers;
    }

    inline int getDeltaElo(){
        return m_deltaElo;
    }

    inline int getNumPlayersTeam() {
        return m_numPlayersTeam;
    }

    inline int getNumTotalMatches() {
        return m_numTotalMatches;
    }

private:
    int m_numPlayers;
    int m_numPlayersTeam;
    int m_deltaElo;
    int m_numTotalMatches;
    shared_ptr<PlayersDB> m_playersDB;
    shared_ptr<Statistics> m_statistics;
    shared_ptr<EloCalculator> m_eloCalculator;
    shared_ptr<Result> m_result;
    shared_ptr<MatchSimulator> m_matchSimulator;
    shared_ptr<TeamBuilder> m_teamBuilder;
    shared_ptr<MatchMaker> m_matchMaker;
    shared_ptr<ExcelExporter> m_excelExporter;
};

