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
    res = lua_tonumber(m_L, -1);
    lua_pop(m_L, 1);
    return res;

}
