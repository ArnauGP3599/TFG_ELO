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

class Simulation
{
public:
    void init(int numPlayers, int numPlayersTeam, int deltaElo, int numTotalMatches);
    void startSimulation();

    inline int getNumPlayers() {
        return numPlayers;
    }

    inline int getDeltaElo(){
        return deltaElo;
    }

    inline int getNumPlayersTeam() {
        return numPlayersTeam;
    }

    inline int getNumTotalMatches() {
        return numTotalMatches;
    }

private:
    int numPlayers, numPlayersTeam, deltaElo, numTotalMatches;
    shared_ptr<PlayersDB> playersDB;
    shared_ptr<Statistics> statistics;
    shared_ptr<EloCalculator> eloCalculator;
    shared_ptr<Result> result;
    shared_ptr<MatchSimulator> matchSimulator;
    shared_ptr<TeamBuilder> teamBuilder;
    shared_ptr<MatchMaker> matchMaker;
};

