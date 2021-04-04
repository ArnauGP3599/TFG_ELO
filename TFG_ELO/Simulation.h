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
    void init();

    inline int getNumPlayers() {
        return numPlayers;
    }

    inline int getDeltaElo(){
        return deltaElo;
    }

    inline int getNumPlayersTeam() {
        return numPlayersTeam;
    }

private:
    int numPlayers, numPlayersTeam, deltaElo;
};

