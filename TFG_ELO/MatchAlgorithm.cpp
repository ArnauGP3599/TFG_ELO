#include "Precompiled.h"
#include "MatchAlgorithm.h"

bool MatchAlgorithm::checkLua(lua_State* L, int r) {
    if (r != LUA_OK) {
        string error = lua_tostring(L, -1);
        cout << error << endl;
        return false;
    }
    return true;
}

int MatchAlgorithm::playMatchTeam() {
    //return rand() % 100;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    int res = 0;
    if (checkLua(L, luaL_dofile(L, "LuaScript.lua"))) {
        lua_getglobal(L, "sum");

        if (lua_pcall(L, 0, 1, 0) != 0)
            cout << "error running function `sum': %s" << endl;

        if (!lua_isnumber(L, -1))
            cout << "function `f' must return a number" << endl;
        res = lua_tonumber(L, -1);
        lua_pop(L, 1); 
        cout << "El resultat és " << res << endl;
    }
    lua_close(L);
    return res;
}
