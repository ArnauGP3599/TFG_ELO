#include "Precompiled.h"
#include "Simulation.h"

bool Simulation::checkLua(lua_State* L, int r) {
    if (r != LUA_OK) {
        string error = lua_tostring(L, -1);
        cout << error << endl;
        return false;
    }
    return true;
}

bool Simulation::initLua_State() {
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    return checkLua(m_L, luaL_dofile(m_L, "../../../TFG_ELO/LuaScript.lua"));
}

void Simulation::initLua() {
    lua_getglobal(m_L, "initLua");

    if (lua_pcall(m_L, 0, 0, 0) != 0)
        cout << "error running function `LuaScript': %s" << endl;
}

Simulation::InitResult Simulation::init(int i_numPlayers, int i_numPlayersTeam, int i_numTeamsMatch, int i_deltaElo, int i_numTotalMatches) {
    if (!initLua_State()) {
        return InitResult::Failed;
    }
    initLua();
    m_numPlayers = i_numPlayers;
    m_numPlayersTeam = i_numPlayersTeam;
    m_numTeamsMatch = i_numTeamsMatch;
    m_deltaElo = i_deltaElo;
    m_numTotalMatches = i_numTotalMatches;

    m_propertiesDB = make_shared<PropertiesDB>(m_L);
    m_propertiesDB->obtainProperties();
    
    m_teamBuilder = make_shared<TeamBuilder>(m_numPlayersTeam, m_deltaElo);
    m_matchMaker = make_shared<MatchMaker>(m_deltaElo, m_numTeamsMatch);
    m_matchSimulator = make_shared<MatchSimulator>(m_L);
    m_eloCalculator = make_shared<EloCalculator>(m_L);
    return InitResult::Success;
}

vector<vector<int>> Simulation::startSimulation() {
    shared_ptr<PlayersDB> m_playersDB = make_shared<PlayersDB>();
    m_playersDB->init();
    m_playersDB->addPlayers(m_numPlayers);
    //m_propertiesDB->createPlayersProperties(m_playersDB->getPlayersSize());
    m_propertiesDB->obtainPlayersProperties(m_playersDB);
    m_matchMaker->init();
    shared_ptr<Statistics> m_statistics = make_shared<Statistics>();
    m_statistics->init(m_playersDB);
    shared_ptr<Result> m_result = make_shared<Result>();
    m_result->init(m_playersDB);

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
    lua_close(m_L);
    return m_statistics->getStatistics();
}