#pragma once
#include "Property.h"
#include "playersDB.h"

extern "C" {
#include "Lua542/include/lua.h"
#include "Lua542/include/lauxlib.h"
#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua542/liblua54.a")
#endif // _WIN32

class PropertiesDB
{
public:
	PropertiesDB(lua_State* i_L);
	void obtainProperties();
	void obtainPlayersProperties(shared_ptr<PlayersDB>& i_PlayersDB);
	//void createPlayersProperties(const int& playersSize);
	vector <shared_ptr<Property>> getProperties();
private:
	lua_State* m_L;
	vector<shared_ptr<Property>> m_properties;
};

