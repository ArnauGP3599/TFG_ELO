#pragma once

#include <stdlib.h>  

class Player
{
	public:
		Player();
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

	private:
		int m_id, m_elo, m_numMatches;
		
};

