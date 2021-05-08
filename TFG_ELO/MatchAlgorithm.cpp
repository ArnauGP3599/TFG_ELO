#include "Precompiled.h"
#include "MatchAlgorithm.h"

MatchAlgorithm::MatchAlgorithm(lua_State* i_L) {
    m_L = i_L;
}

/*int MatchAlgorithm::playMatchTeam() {
    //return rand() % 100;
    int res = 0;
    lua_getglobal(m_L, "puntuationTeam");

    if (lua_pcall(m_L, 0, 1, 0) != 0)
        cout << "error running function `puntuationTeam': %s" << endl;

    if (!lua_isnumber(m_L, -1))
        cout << "function `puntuationTeam' must return a number" << endl;
    res = (int)lua_tonumber(m_L, -1);
    lua_pop(m_L, 1); 
    cout << "El resultat es " << res << endl;
    return res;
}*/

void MatchAlgorithm::playMatch(shared_ptr<Match>& match) {
    //matchParticipants
    cleanTable();
    lua_getglobal(m_L, "matchParticipants");
    vector<shared_ptr<Team>> teams = match->getTeamsMatch();
    for (int i = 0; i < teams.size(); i++) {
        //push name?
        string teamName = "Team" + to_string(teams[i]->getId());
        //ficar aqui si es fa
        lua_newtable(m_L);
        vector<shared_ptr<Player>> playersTeam = teams[i]->getPlayersTeam();
        for (int j = 0; j < playersTeam.size(); j++) {
            lua_newtable(m_L);
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
    }
    lua_pop(m_L, -1);

    lua_getglobal(m_L, "playMatch");
    if (lua_pcall(m_L, 0, 0, 0)){
        cout << "error running function `playMatch': %s" << endl;
        cout << lua_tostring(m_L, -1) << endl;
    }
    lua_pop(m_L, -1);
}

void MatchAlgorithm::cleanTable() {
    lua_getglobal(m_L, "cleanMatchParticipants");
    if(lua_pcall(m_L, 0, 0, 0))
        cout << "error running function `cleanMatchParticipants': %s" << endl;
    lua_pop(m_L, -1);
}

vector<int> MatchAlgorithm::getResults() {
    vector<int> results;
    lua_getglobal(m_L, "classification");    
    if (lua_istable(m_L, -1)) {
        int totalElements = lua_rawlen(m_L, 1);
        for (int i = 1; i <= totalElements; i++) {
            lua_rawgeti(m_L, -1, i);
            lua_pushnil(m_L);
            while (lua_next(m_L, -2) != 0)
            {
                int posTeam = lua_tonumber(m_L, -1);
                results.emplace_back(posTeam);
                lua_pop(m_L, 1);
            }
            lua_pop(m_L, 1);
        }
    }  
    /*for (int i = 0; i < m_properties.size(); i++) {
        cout << "Propietat " << m_properties[i]->getName() << endl;
    }*/
    lua_pop(m_L, 1);
    return results;
}