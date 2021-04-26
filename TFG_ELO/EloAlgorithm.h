#pragma once

extern "C" {
	#include "Lua542/include/lua.h"
	#include "Lua542/include/lauxlib.h"
	#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua542/liblua54.a")
#endif // _WIN32

class EloAlgorithm
{
public:
	EloAlgorithm(lua_State* i_L);
	double getExpectedScore(int teamA, int teamB);

private:
	lua_State* m_L;
};

