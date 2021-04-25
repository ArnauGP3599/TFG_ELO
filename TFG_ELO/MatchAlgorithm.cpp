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
    cout << "El resultat és " << res << endl;
    return res;
}

/*void MatchAlgorithm::prova() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    struct p {
        string name;
        string cognom;
        int num;
    };
    vector<p> pp;
    if (checkLua(L, luaL_dofile(L, "LuaScript.lua"))) {
        lua_getglobal(L, "prova");
        cout << "Mida " << lua_rawlen(L, 1) << endl;
        for (int i = 0; i < 2; i++) {
            if (lua_istable(L, -1)) {
                int j = i + 1;
                cout << "j " << j << endl;
                lua_rawgeti(L, -1, j);
                cout << "mida " << lua_rawlen(L, 1) << endl;
                p p1;
                lua_pushstring(L, "Name");
                lua_gettable(L, -2);
                p1.name = lua_tostring(L, -1);
                lua_pop(L, 1);

                lua_pushstring(L, "Cognom");
                lua_gettable(L, -2);
                p1.cognom = lua_tostring(L, -1);
                lua_pop(L, 1);

                lua_pushstring(L, "Num");
                lua_gettable(L, -2);
                p1.num = lua_tonumber(L, -1);
                lua_pop(L, 1);
                pp.emplace_back(p1);

                cout << lua_gettop(L) << endl;
                lua_pop(L, 1);
                cout << "després del pop " <<  lua_gettop(L) << endl;
            }
        }

    }
    for (int i = 0; i < pp.size(); i++) {
        cout << "Em dic " << pp[i].name << " " << pp[i].cognom << " i soc el numero " << pp[i].num << endl;
    }
    lua_close(L);
}*/
