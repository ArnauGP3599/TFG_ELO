#include "Precompiled.h"
#include "MatchAlgorithm.h"

MatchAlgorithm::MatchAlgorithm(lua_State* i_L) {
    m_L = i_L;
}

int MatchAlgorithm::playMatchTeam() {
    //return rand() % 100;
    int res = 0;
    lua_getglobal(m_L, "sum");

    if (lua_pcall(m_L, 0, 1, 0) != 0)
        cout << "error running function `sum': %s" << endl;

    if (!lua_isnumber(m_L, -1))
        cout << "function `f' must return a number" << endl;
    res = lua_tonumber(m_L, -1);
    lua_pop(m_L, 1); 
    return res;
}