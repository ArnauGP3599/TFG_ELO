#pragma once
#include "Player.h"

class Team
{
	public:

		Team(int i_id);

		inline int getId() {
			return m_id;
		}

		inline void setId(int i_id) {
			m_id = i_id;
		}

		inline int getEloTeam(){
			return m_eloTeam;
		}

		inline void setEloTeam(int i_eloTeam){
			m_eloTeam = i_eloTeam;
		}

		inline vector<shared_ptr<Player>> getPlayersTeam() {
			return playersTeam;
		}

		void addPlayerInTeam(shared_ptr<Player>& player);


	
	private:
		int m_id, m_eloTeam;
		vector<shared_ptr<Player>> playersTeam;
};

