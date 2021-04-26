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
        const char* property = lua_tostring(m_L, -1);
        shared_ptr<Property> prop = make_shared<Property>(property);
        m_properties.emplace_back(prop);
        lua_pop(m_L, 1);
    }
    for (int i = 0; i < m_properties.size(); i++) {
        cout << "Propietat " << m_properties[i]->getName() << endl;
    }
    lua_pop(m_L, 1);
}

void PropertiesDB::obtainPlayersProperties(shared_ptr<PlayersDB>& i_PlayersDB) {
    vector<shared_ptr<Player>> players = i_PlayersDB->getPlayers();
    lua_getglobal(m_L, "playerProperties");
    for (int j = 1; j <= players.size(); j++) {
        if (lua_istable(m_L, -1)) {
            lua_rawgeti(m_L, -1, j);
            const char* ID = m_properties[0]->getName();
            lua_pushstring(m_L, ID);
            lua_gettable(m_L, -2);
            int id = lua_tonumber(m_L, -1);
            lua_pop(m_L, 1);

            for (int i = 1; i < m_properties.size(); i++) {
                const char* propertyName = m_properties[i]->getName();
                lua_pushstring(m_L, propertyName);
                lua_gettable(m_L, -2);
                int value = lua_tonumber(m_L, -1);
                lua_pop(m_L, 1);
                players[id]->addProperty(propertyName, value);
            }
            lua_pop(m_L, 1);
        }
    }
    lua_pop(m_L, 1);
}

vector<shared_ptr<Property>> PropertiesDB::getProperties() {
	return m_properties;
}