#pragma once
#include "Player.h"

class Team
{
	public:

		Team(int id);

		inline int getId() {
			return id;
		}

		inline void setId(int id) {
			this->id = id;
		}

		inline int getEloTeam(){
			return eloTeam;
		}

		inline void setEloTeam(int eloTeam){
			this->eloTeam = eloTeam;
		}

		inline vector<shared_ptr<Player>> getPlayersTeam() {
			return playersTeam;
		}

		void addPlayerInTeam(shared_ptr<Player>& player);


	
	private:
		int id, eloTeam;
		vector<shared_ptr<Player>> playersTeam;
};

