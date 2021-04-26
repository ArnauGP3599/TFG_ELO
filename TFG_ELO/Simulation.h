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
#include "PropertiesDB.h"

extern "C" {
    #include "Lua542/include/lua.h"
    #include "Lua542/include/lauxlib.h"
    #include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua542/liblua54.a")
#endif // _WIN32

class Simulation
{
public:
    void init(int i_numPlayers, int i_numPlayersTeam, int i_deltaElo, int i_numTotalMatches);
    bool initLua_State();
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
    shared_ptr<PropertiesDB> m_propertiesDB;
    shared_ptr<Statistics> m_statistics;
    shared_ptr<EloCalculator> m_eloCalculator;
    shared_ptr<Result> m_result;
    shared_ptr<MatchSimulator> m_matchSimulator;
    shared_ptr<TeamBuilder> m_teamBuilder;
    shared_ptr<MatchMaker> m_matchMaker;
    shared_ptr<ExcelExporter> m_excelExporter;

    bool checkLua(lua_State* L, int r);
    lua_State* m_L;
};

