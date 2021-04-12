#include "Precompiled.h"
#include "MatchMaker.h"

MatchMaker::MatchMaker(int i_deltaElo) {
	m_deltaElo = i_deltaElo;
	idMatch = 0;
}

vector<shared_ptr<Match>> MatchMaker::searchMatch(const vector < shared_ptr<Team>>& teams) {
	vector<shared_ptr<Match>> matches;
	int numMatches = teams.size() / 2;
	for (int i = 0; i < numMatches; i++) {
		shared_ptr<Match> m = make_shared<Match>(idMatch);
		for (int j = i * 2; j < (i + 1) * 2; j++){
			m->addTeamMatch(teams[j]);
		}
		matches.emplace_back(m);
		idMatch++;
	}
	return move(matches);
}

