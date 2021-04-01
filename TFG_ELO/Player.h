#pragma once

#include <stdlib.h>  

class Player
{
	public:
		Player();
		Player(int id);

		inline int getId() {
			return id;
		}

		inline void setId(int id) {
			this->id = id;
		}

		inline int getElo() {
			return elo;
		}
		
		inline void setElo(int elo) {
			this->elo = elo;
		}

		inline int getNumMatches() {
			return numMatches;
		}

		inline void setNumMatches(int numMatches) {
			this->numMatches = numMatches;
		}

	private:
		int id, elo, numMatches;
		
};

