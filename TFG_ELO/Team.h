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

		inline int getTotalEloTeam() {
			return m_eloTotalTeam;
		}

		inline void setTotalEloTeam(int i_totalEloTeam) {
			m_eloTotalTeam = i_totalEloTeam;
		}

		inline int getMinValue() {
			return m_minValue;
		}

		inline void setMinValue(int i_minValue) {
			m_minValue = i_minValue;
		}

		inline int getMaxValue() {
			return m_maxValue;
		}

		inline void setMaxValue(int i_maxValue) {
			m_maxValue = i_maxValue;
		}

		inline int getEloFirstPlayer() {
			return m_eloFirstPlayer;
		}

		inline void setEloFirstPlayer(int i_eloFirstPlayer) {
			m_eloFirstPlayer = i_eloFirstPlayer;
		}

		inline vector<shared_ptr<Player>> getPlayersTeam() {
			return m_playersTeam;
		}

		void addPlayerInTeam(const shared_ptr<Player>& player);

		int getNumPlayersTeam();

		void addEloTeam(int i_elo);


	
	private:
		int m_id, m_eloTotalTeam, m_eloTeam;
		int m_minValue, m_maxValue;
		int m_eloFirstPlayer;
		vector<shared_ptr<Player>> m_playersTeam;
};

