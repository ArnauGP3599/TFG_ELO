#pragma once
#include "Team.h"

class Match
{
public:
	Match(int i_id);

	inline int getId() {
		return m_id;
	}

	inline void setId(int i_id) {
		m_id = i_id;
	}

	inline vector<shared_ptr<Team>> getTeamsMatch() {
		return m_teamsMatch;
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

	inline int getEloFirstTeam() {
		return m_eloFirstTeam;
	}

	inline void setEloFirstTeam(int i_eloFirstTeam) {
		m_eloFirstTeam = i_eloFirstTeam;
	}

	void addTeamMatch(const shared_ptr<Team>& i_team);

	int getNumTeamsMatch();

private:
	int m_id;
	int m_minValue, m_maxValue;
	int m_eloFirstTeam;
	vector<shared_ptr<Team>> m_teamsMatch;
};

