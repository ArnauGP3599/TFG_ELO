#pragma once

#include <stdlib.h>  
#include <map>

class Player
{
	public:
		Player(int i_id);

		inline int getId() {
			return m_id;
		}

		inline void setId(int i_id) {
			m_id = i_id;
		}

		inline int getElo() {
			return m_elo;
		}
		
		inline void setElo(int i_elo) {
			m_elo = i_elo;
		}

		inline int getNumMatches() {
			return m_numMatches;
		}

		inline void setNumMatches(int i_numMatches) {
			this->m_numMatches = i_numMatches;
		}

		void addProperty(const string i_name, const int i_value);
		
		inline map<string, int> getProperties() {
			return m_properties;
		}

	private:
		int m_id, m_elo, m_numMatches;
		map<string, int> m_properties;
		
};

