#include "Precompiled.h"
#include "EloAlgorithm.h"

EloAlgorithm::EloAlgorithm(lua_State* i_L) {
	m_L = i_L;
}

double EloAlgorithm::getExpectedScore(int teamA, int teamB) {
	/*float deltaTeam = teamB - teamA;
	float divElev = deltaTeam / 800.f;
	float elev = pow(10.f, divElev);
	return (1.f / (1.f + elev));*/

    double res = 0;
    lua_getglobal(m_L, "calculateEloScore");  /* function to be called */
    lua_pushnumber(m_L, teamA);   /* push 1st argument */
    lua_pushnumber(m_L, teamB);

    if (lua_pcall(m_L, 2, 1, 0) != 0)
        cout << "error running function `calculateEloScore': %s" << endl;

    if (!lua_isnumber(m_L, -1))
        cout << "function `calculateEloScore' must return a number" << endl;
    res = (double)lua_tonumber(m_L, -1);
    lua_pop(m_L, 1);
    return res;

}

map<IDPlayer, EloScore> EloAlgorithm::calculateEloScore(shared_ptr<Classification>& classification) {
    map<IDPlayer, EloScore> deltaEloPlayers;
    
    lua_getglobal(m_L, "calculateEloScore");
    if (lua_isfunction(m_L, -1)) {
        map<PositionClassification, vector<shared_ptr<Team>>> classif = classification->getClasification();
        lua_newtable(m_L);
        int pos3 = 0;
        for (auto it = classif.begin(); it != classif.end(); it++) {
            lua_newtable(m_L);
            lua_pushnumber(m_L, it->first);
            lua_setfield(m_L, -2, "positionTeam");
            vector<shared_ptr<Team>> teams = it->second;
            for (int i = 0; i < teams.size(); i++) {
                lua_newtable(m_L);
                lua_pushnumber(m_L, teams[i]->getEloTeam());
                lua_setfield(m_L, -2, "eloTeam");
                lua_newtable(m_L);
                vector<shared_ptr<Player>> playersTeam = teams[i]->getPlayersTeam();
                for (int j = 0; j < playersTeam.size(); j++) {
                    lua_newtable(m_L);
                    lua_pushnumber(m_L, playersTeam[j]->getId());
                    lua_setfield(m_L, -2, "idPlayer");
                    lua_pushnumber(m_L, playersTeam[j]->getElo());
                    lua_setfield(m_L, -2, "eloPlayer");
                    map<string, int> playersProperties = playersTeam[j]->getProperties();
                    for (auto k = playersProperties.begin(); k != playersProperties.end(); k++) {
                        lua_pushnumber(m_L, k->second);
                        lua_setfield(m_L, -2, k->first.c_str());
                    }
                    int pos = j + 1;
                    lua_rawseti(m_L, -2, pos);
                }
                int pos2 = i + 1;
                lua_rawseti(m_L, -2, pos2);
                lua_rawseti(m_L, -2, pos2);
            }
            pos3++;
            lua_rawseti(m_L, -2, pos3);
        }
        if (lua_pcall(m_L, 1, 1, 0)) {
            cout << "error running function `calculateEloScore': %s" << endl;
            cout << lua_tostring(m_L, -1) << endl;
        }
        if (lua_istable(m_L, -1)) {
            int totalElements = lua_rawlen(m_L, 1);
            for (int i = 1; i <= totalElements; i++) {
                lua_rawgeti(m_L, -1, i);
                //lua_pushnil(m_L);

                lua_pushstring(m_L, "idPlayer");
                lua_gettable(m_L, -2);
                int idPlayer = lua_tonumber(m_L, -1);
                lua_pop(m_L, 1);
                lua_pushstring(m_L, "deltaEloPlayer");
                lua_gettable(m_L, -2);
                int deltaElo = lua_tonumber(m_L, -1);
                lua_pop(m_L, 1);

                pair<IDPlayer, EloScore> p(idPlayer, deltaElo);
                deltaEloPlayers.emplace(p);

                lua_pop(m_L, 1);
            }
        }
        lua_pop(m_L, 1);
    }

    return deltaEloPlayers;
}
