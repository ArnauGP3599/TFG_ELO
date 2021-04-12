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
    void startSimulation();

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
    shared_ptr<PlayersDB> playersDB;
    shared_ptr<Statistics> statistics;
    shared_ptr<EloCalculator> eloCalculator;
    shared_ptr<Result> result;
    shared_ptr<MatchSimulator> matchSimulator;
    shared_ptr<TeamBuilder> teamBuilder;
    shared_ptr<MatchMaker> matchMaker;
    shared_ptr<Exporter> exporter;
    shared_ptr<ExcelExporter> excelExporter;
};

