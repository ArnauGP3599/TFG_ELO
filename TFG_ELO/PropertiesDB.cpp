#include "Precompiled.h"
#include "PropertiesDB.h"

PropertiesDB::PropertiesDB(lua_State* i_L) {
	m_L = i_L;
}

void PropertiesDB::obtainProperties() {
    lua_getglobal(m_L, "properties");
    lua_pushnil(m_L);
    while (lua_next(m_L, -2) != 0)
    {
        string property = lua_tostring(m_L, -1);
        shared_ptr<Property> prop = make_shared<Property>(property);
        m_properties.emplace_back(prop);
        lua_pop(m_L, 1);
    }
    /*for (int i = 0; i < m_properties.size(); i++) {
        cout << "Propietat " << m_properties[i]->getName() << endl;
    }*/
    lua_pop(m_L, 1);
}

void PropertiesDB::obtainPlayersProperties(shared_ptr<PlayersDB>& i_PlayersDB) {
    vector<shared_ptr<Player>> players = i_PlayersDB->getPlayers();
    //lua_getglobal(m_L, "playerProperties");
    lua_getglobal(m_L, "getPlayerProperties");
    lua_pushnumber(m_L, players.size());
    if (lua_pcall(m_L, 1, 1, 0) != 0){
        cout << "error running function `getPlayerProperties': %s" << endl;
        cout << lua_tostring(m_L, -1) << endl;
    }
    if (lua_istable(m_L, -1)) {
        for (int j = 1; j <= players.size(); j++) {
            if (lua_istable(m_L, -1)) {
                lua_rawgeti(m_L, -1, j);
                string ID = m_properties[0]->getName();
                lua_pushstring(m_L, ID.c_str());
                lua_gettable(m_L, -2);
                int id = lua_tonumber(m_L, -1);
                lua_pop(m_L, 1);

                string eloP = m_properties[1]->getName();
                lua_pushstring(m_L, eloP.c_str());
                lua_gettable(m_L, -2);
                int eloPlayer = lua_tonumber(m_L, -1);
                players[id]->setElo(eloPlayer);
                lua_pop(m_L, 1);

                for (int i = 2; i < m_properties.size(); i++) {
                    string propertyName = m_properties[i]->getName();
                    lua_pushstring(m_L, propertyName.c_str());
                    lua_gettable(m_L, -2);
                    int value = lua_tonumber(m_L, -1);
                    lua_pop(m_L, 1);
                    players[id]->addProperty(propertyName, value);
                }
                lua_pop(m_L, 1);
            }
        }
    }
    lua_pop(m_L, 1);
}

/*void PropertiesDB::createPlayersProperties(const int& playersSize) {
    lua_getglobal(m_L, "playerProperties");
    for (int i = 0; i < playersSize; i++) {
        lua_newtable(m_L);
        int var = 1;
        for (int j = 0; j < m_properties.size(); j++) {
            if (m_properties[j]->getName() == "ID") {
                lua_pushnumber(m_L, i);
            }
            else {
                int value = i + var;
                lua_pushnumber(m_L, value);
            }
            lua_setfield(m_L, -2, m_properties[j]->getName().c_str());
            var++;
        }
        int pos = i + 1;
        lua_rawseti(m_L, -2, pos);
    }
    lua_pop(m_L, 1);
}*/

vector<shared_ptr<Property>> PropertiesDB::getProperties() {
	return m_properties;
}