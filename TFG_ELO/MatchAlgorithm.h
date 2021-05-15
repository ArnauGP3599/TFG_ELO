#pragma once
#include "Match.h"

extern "C" {
	#include "Lua542/include/lua.h"
	#include "Lua542/include/lauxlib.h"
	#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua542/liblua54.a")
#endif // _WIN32

class MatchAlgorithm
{
public:
	MatchAlgorithm(lua_State* i_L);
	//int playMatchTeam();
	vector<int> playMatch(shared_ptr<Match>& match);
	//vector<int> getResults();

private:
	lua_State* m_L;
};

