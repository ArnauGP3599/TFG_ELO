#include "pch.h"
#include "PlayersDB.h"
#include "Player.h"
#include "PropertiesDB.h"
#include "Simulation.h"

#include <memory>
#include <vector>
#include <string>

#include "TeamBuilder.h"
#include"MatchMaker.h"
#include "Team.h"

/*lua_State* luanewStateDummy() {
	return luaL_newstate();
}*/

class EloTestFixure : public testing::Test
{
public:

	lua_State* m_L;
	std::vector<std::shared_ptr<Player> > players;

	void SetUp()override {
		//init lua
		m_L = luaL_newstate();
		luaL_openlibs(m_L);
		

		if (luaL_dofile(m_L, "../TFG_ELO/LuaScript.lua") != LUA_OK) {
			string error = lua_tostring(m_L, -1);
			cout << error << endl;
		}

		//createPlayers
		for (int i = 0; i < 100; i++) {
			std::shared_ptr<Player> p = std::make_shared<Player>(i);
			p->setElo(i * 10);
			p->addProperty("Strength", i);
			p->addProperty("Armor", i);
			players.emplace_back(p);
		}
	}

	void TearDown() override {
		lua_close(m_L);
	}
};



/*class EloTestFixure : public testing::Test
{
public:
	lua_State* m_L;
	std::vector<std::shared_ptr<Player> > players;

	void SetUp() override {
		//init lua
		m_L = luaL_newstate();
		luaL_openlibs(m_L);

		//createPlayers
		for (int i = 0; i < 100; i++) {
			std::shared_ptr<Player> p = std::make_shared<Player>(i);
			p->setElo(i * 10);
			p->addProperty("Strength", i);
			p->addProperty("Armor", i);
			players.emplace_back(p);
		}

	}

	void TearDown() override {
		lua_close(m_L);
	}
}; */

TEST_F(EloTestFixure, CreateNumTeams) {
	std::shared_ptr<TeamBuilder> t = std::make_shared<TeamBuilder>(5, 100);
	std::vector<std::shared_ptr<Team>> res = t->createTeams(players);
	ASSERT_EQ(20, res.size());
}

TEST_F(EloTestFixure, CreateTeamsEasy) {
	std::vector<std::shared_ptr<Team>> comp;
	int numPlayers = 5;
	int id = 0;
	std::shared_ptr<Team> t = std::make_shared<Team>(id);
	for (int i = 0; i < 100; i++) {
		t->addPlayerInTeam(players[i]);
		t->addEloTeam(players[i]->getElo());
		if (t->getNumPlayersTeam() == numPlayers) {
			comp.emplace_back(t);
			id++;
			t = std::make_shared<Team>(id);
		}
	}
	std::shared_ptr<TeamBuilder> t2 = std::make_shared<TeamBuilder>(numPlayers, 100);
	std::vector<std::shared_ptr<Team>> res = t2->createTeams(players);
	for (int i = 0; i < res.size(); i++) {
		std::vector<std::shared_ptr<Player> > compPlayer = comp[i]->getPlayersTeam();
		std::vector<std::shared_ptr<Player> > resPlayer = res[i]->getPlayersTeam();
		for (int j = 0; j < numPlayers; j++) {
			ASSERT_EQ(resPlayer[j], compPlayer[j]);
		}
	}
}

TEST_F(EloTestFixure, CreateNumTeamsZero) {
	std::shared_ptr<TeamBuilder> t = std::make_shared<TeamBuilder>(5, 100);
	players.clear();
	std::vector<std::shared_ptr<Team>> res = t->createTeams(players);
	ASSERT_EQ(0, res.size());
}

TEST_F(EloTestFixure, CreateNumTeamsOdd) {
	std::shared_ptr<TeamBuilder> t = std::make_shared<TeamBuilder>(7, 100);
	std::vector<std::shared_ptr<Team>> res = t->createTeams(players);
	ASSERT_EQ(14, res.size());
}

TEST_F(EloTestFixure, CreateTeamsOddPlayersTeams) {
	std::vector<std::shared_ptr<Team>> comp;
	int numPlayers = 7;
	int id = 0;
	std::shared_ptr<Team> t = std::make_shared<Team>(id);
	for (int i = 0; i < 100; i++) {
		t->addPlayerInTeam(players[i]);
		t->addEloTeam(players[i]->getElo());
		if (t->getNumPlayersTeam() == numPlayers) {
			comp.emplace_back(t);
			id++;
			t = std::make_shared<Team>(id);
		}
	}
	std::shared_ptr<TeamBuilder> t2 = std::make_shared<TeamBuilder>(numPlayers, 100);
	std::vector<std::shared_ptr<Team>> res = t2->createTeams(players);
	for (int i = 0; i < res.size(); i++) {
		std::vector<std::shared_ptr<Player> > compPlayer = comp[i]->getPlayersTeam();
		std::vector<std::shared_ptr<Player> > resPlayer = res[i]->getPlayersTeam();
		for (int j = 0; j < numPlayers; j++) {
			ASSERT_EQ(resPlayer[j], compPlayer[j]);
		}
	}
}

TEST_F(EloTestFixure, CreateNumTeamsComplicated) {
	for (int i = 0; i < 50; i++) {
		if (i % 2 != 0) {
			players[i]->setElo(players[i + 50]->getElo());
			players[i + 50]->setElo(i * 10);
		}
	}
	std::shared_ptr<TeamBuilder> t = std::make_shared<TeamBuilder>(5, 100);
	std::vector<std::shared_ptr<Team>> res = t->createTeams(players);
	ASSERT_EQ(20, res.size());
}

TEST_F(EloTestFixure, CreateTeamsComplicated) {
	for (int i = 0; i < 50; i++) {
		if (i % 2 != 0) {
			players[i]->setElo(players[i + 50]->getElo());
			players[i + 50]->setElo(i * 10);
		}
	}
	std::vector<std::shared_ptr<Team>> comp;
	int numPlayers = 5;
	int id = 1;
	std::shared_ptr<Team> t = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(id);
	for (int i = 0; i < 100; i++) {
		if (i % 2 == 0) {
			t->addPlayerInTeam(players[i]);
			t->addEloTeam(players[i]->getElo());
			if (t->getNumPlayersTeam() == numPlayers) {
				comp.emplace_back(t);
				id++;
				t = std::make_shared<Team>(id);
			}
		}
		else {
			t2->addPlayerInTeam(players[i]);
			t2->addEloTeam(players[i]->getElo());
			if (t2->getNumPlayersTeam() == numPlayers) {
				comp.emplace_back(t2);
				id++;
				t2 = std::make_shared<Team>(id);
			}
		}
		
	}
	std::shared_ptr<TeamBuilder> t3 = std::make_shared<TeamBuilder>(numPlayers, 100);
	std::vector<std::shared_ptr<Team>> res = t3->createTeams(players);
	for (int i = 0; i < res.size(); i++) {
		std::vector<std::shared_ptr<Player> > compPlayer = comp[i]->getPlayersTeam();
		std::vector<std::shared_ptr<Player> > resPlayer = res[i]->getPlayersTeam();
		for (int j = 0; j < numPlayers; j++) {
			ASSERT_EQ(resPlayer[j], compPlayer[j]);
		}
	}
}

TEST_F(EloTestFixure, CreateNumMatches) {
	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		t->setEloTeam(i * 50);
		teams.emplace_back(t);
	}
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(100, 2);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(10, res.size());
}

TEST_F(EloTestFixure, CreateMatchesEasy) {
	std::vector<std::shared_ptr<Match>> comp;
	int numTeamsMatch = 2;
	int id = 0;

	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		t->setEloTeam(i * 50);
		teams.emplace_back(t);
	}
	std::shared_ptr<Match> m = std::make_shared<Match>(id);
	for (int i = 0; i < teams.size(); i++) {
		m->addTeamMatch(teams[i]);
		if (m->getNumTeamsMatch() == numTeamsMatch) {
			comp.emplace_back(m);
			id++;
			m = std::make_shared<Match>(id);
		}
	}
	std::shared_ptr<MatchMaker> mm = std::make_shared<MatchMaker>(100, 2);
	mm->init();
	std::vector<std::shared_ptr<Match>> res = mm->searchMatch(teams);

	for (int i = 0; i < res.size(); i++) {
		ASSERT_EQ(res[i]->getId(), comp[i]->getId());
		std::vector<std::shared_ptr<Team> > compTeam = comp[i]->getTeamsMatch();
		std::vector<std::shared_ptr<Team> > resTeam = res[i]->getTeamsMatch();
		for (int j = 0; j < numTeamsMatch; j++) {
			ASSERT_EQ(resTeam[j]->getId(), compTeam[j]->getId());
		}
	}
}

TEST_F(EloTestFixure, CreateNumMatchesZero) {
	std::vector<std::shared_ptr<Team>> teams;
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(100, 2);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(0, res.size());
}

TEST_F(EloTestFixure, CreateNumMatchesZeroElo) {
	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		t->setEloTeam(i * 50);
		teams.emplace_back(t);
	}
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(0, 2);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(0, res.size());
}
//	--gtest_filter="*xxxx*"

TEST_F(EloTestFixure, CreateMatches3Teams) {
	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		t->setEloTeam(i * 50);
		teams.emplace_back(t);
	}
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(100, 3);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(6, res.size());
}

TEST_F(EloTestFixure, CreateMatchesManyTeams) {
	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 23; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		t->setEloTeam(i * 50);
		teams.emplace_back(t);
	}
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(100, 25);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(0, res.size());
}

TEST_F(EloTestFixure, CreateNumMatchesComplicated) {
	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		if(i % 2 == 0) t->setEloTeam(i * 50);
		else t->setEloTeam(i * 300);
		teams.emplace_back(t);
	}
	std::shared_ptr<MatchMaker> m = std::make_shared<MatchMaker>(250, 3);
	std::vector<std::shared_ptr<Match>> res = m->searchMatch(teams);
	ASSERT_EQ(3, res.size());
}

TEST_F(EloTestFixure, CreateMatchesComplicated) {
	std::vector<std::shared_ptr<Match>> comp;
	int numTeamsMatch = 2;
	int id = 0;

	std::vector<std::shared_ptr<Team>> teams;
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Team> t = std::make_shared<Team>(i);
		if (i % 2 == 0) t->setEloTeam(i * 50);
		else t->setEloTeam(i * 300);
		teams.emplace_back(t);
	}
	std::shared_ptr<Match> m = std::make_shared<Match>(id);

	m->addTeamMatch(teams[0]);
	m->addTeamMatch(teams[2]);
	m->addTeamMatch(teams[4]);
	comp.emplace_back(m);
	id++;
	m = std::make_shared<Match>(id);

	m->addTeamMatch(teams[1]);
	m->addTeamMatch(teams[6]);
	m->addTeamMatch(teams[8]);
	comp.emplace_back(m);
	id++;
	m = std::make_shared<Match>(id);

	m->addTeamMatch(teams[3]);
	m->addTeamMatch(teams[14]);
	m->addTeamMatch(teams[16]);
	comp.emplace_back(m);
	
	std::shared_ptr<MatchMaker> mm = std::make_shared<MatchMaker>(250, 3);
	mm->init();
	std::vector<std::shared_ptr<Match>> res = mm->searchMatch(teams);

	for (int i = 0; i < res.size(); i++) {
		ASSERT_EQ(res[i]->getId(), comp[i]->getId());
		std::vector<std::shared_ptr<Team> > compTeam = comp[i]->getTeamsMatch();
		std::vector<std::shared_ptr<Team> > resTeam = res[i]->getTeamsMatch();
		for (int j = 0; j < numTeamsMatch; j++) {
			ASSERT_EQ(resTeam[j]->getId(), compTeam[j]->getId());
		}
	}
}

TEST_F(EloTestFixure, MatchAlgorithmLua1PlayerTeam) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 0);
	p1->addProperty("Armor", 0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	p2->addProperty("Armor", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 2, 1 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLua2PlayerTeam) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 0);
	p1->addProperty("Armor", 0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	p1 = std::make_shared<Player>(1);
	p1->setElo(10);
	p1->addProperty("Strength", 70);
	p1->addProperty("Armor", 70);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(2);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	p2->addProperty("Armor", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	p2 = std::make_shared<Player>(2);
	p2->setElo(20);
	p2->addProperty("Strength", 20);
	p2->addProperty("Armor", 20);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 1, 2 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLua3Teams) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);
	std::shared_ptr<Team> t3 = std::make_shared<Team>(2);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 0);
	p1->addProperty("Armor", 0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	p2->addProperty("Armor", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	std::shared_ptr<Player> p3 = std::make_shared<Player>(2);
	p3->setElo(300);
	p3->addProperty("Strength", 5);
	p3->addProperty("Armor", 5);
	t3->addPlayerInTeam(p3);
	t3->addEloTeam(p3->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);
	m->addTeamMatch(t3);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 2, 3, 1 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLuaEqualPlayers) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 10);
	p1->addProperty("Armor", 10);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	p2->addProperty("Armor", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 1, 2 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLuaNegativeValues) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", -5);
	p1->addProperty("Armor", -5);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", -10);
	p2->addProperty("Armor", -10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 1, 2 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLuaMoreProperties) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 0);
	p1->addProperty("Armor", 0);
	p1->addProperty("Speed", 0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	p2->addProperty("Armor", 10);
	p2->addProperty("Speed", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 2, 1 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, MatchAlgorithmLuaLessProperties) {
	std::shared_ptr<Match> m = std::make_shared<Match>(0);
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	p1->addProperty("Strength", 0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	p2->addProperty("Strength", 10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());

	m->addTeamMatch(t1);
	m->addTeamMatch(t2);

	std::shared_ptr<MatchAlgorithm> ma = std::make_shared<MatchAlgorithm>(m_L);
	std::vector<int> res = ma->playMatch(m);
	std::vector<int> comp{ 2, 1 };
	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, EloAlgorithmSameEloPlayers) {
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::vector<std::shared_ptr<Team> > vt1;
	std::vector<std::shared_ptr<Team> > vt2;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(10);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	vt1.emplace_back(t1);

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(10);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	vt2.emplace_back(t2);

	std::shared_ptr<Classification> clas = std::make_shared<Classification>();
	clas->addResult(1, vt1);
	clas->addResult(2, vt2);

	std::map<IDPlayer, EloScore> comp;
	pair<IDPlayer, EloScore> pa1(0, 10);
	comp.emplace(pa1);
	pair<IDPlayer, EloScore> pa2(1, -10);
	comp.emplace(pa2);

	std::shared_ptr<EloAlgorithm> ea = std::make_shared<EloAlgorithm>(m_L);
	std::map<IDPlayer, EloScore> res = ea->calculateEloScore(clas);

	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, EloAlgorithmDiffEloPlayersWin1) {
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::vector<std::shared_ptr<Team> > vt1;
	std::vector<std::shared_ptr<Team> > vt2;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	vt1.emplace_back(t1);

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	vt2.emplace_back(t2);

	std::shared_ptr<Classification> clas = std::make_shared<Classification>();
	clas->addResult(1, vt1);
	clas->addResult(2, vt2);

	std::map<IDPlayer, EloScore> comp;
	pair<IDPlayer, EloScore> pa1(0, 10);
	comp.emplace(pa1);
	pair<IDPlayer, EloScore> pa2(1, -10);
	comp.emplace(pa2);

	std::shared_ptr<EloAlgorithm> ea = std::make_shared<EloAlgorithm>(m_L);
	std::map<IDPlayer, EloScore> res = ea->calculateEloScore(clas);

	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, EloAlgorithmDiffEloPlayersWin2) {
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::vector<std::shared_ptr<Team> > vt1;
	std::vector<std::shared_ptr<Team> > vt2;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	vt1.emplace_back(t1);

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(20);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	vt2.emplace_back(t2);

	std::shared_ptr<Classification> clas = std::make_shared<Classification>();
	clas->addResult(1, vt2);
	clas->addResult(2, vt1);

	std::map<IDPlayer, EloScore> comp;
	pair<IDPlayer, EloScore> pa1(0, -9);
	comp.emplace(pa1);
	pair<IDPlayer, EloScore> pa2(1, +9);
	comp.emplace(pa2);

	std::shared_ptr<EloAlgorithm> ea = std::make_shared<EloAlgorithm>(m_L);
	std::map<IDPlayer, EloScore> res = ea->calculateEloScore(clas);

	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, EloAlgorithmMuchDiffEloPlayersWin1) {
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::vector<std::shared_ptr<Team> > vt1;
	std::vector<std::shared_ptr<Team> > vt2;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	vt1.emplace_back(t1);

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(400);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	vt2.emplace_back(t2);

	std::shared_ptr<Classification> clas = std::make_shared<Classification>();
	clas->addResult(1, vt1);
	clas->addResult(2, vt2);

	std::map<IDPlayer, EloScore> comp;
	pair<IDPlayer, EloScore> pa1(0, 15);
	comp.emplace(pa1);
	pair<IDPlayer, EloScore> pa2(1, -15);
	comp.emplace(pa2);

	std::shared_ptr<EloAlgorithm> ea = std::make_shared<EloAlgorithm>(m_L);
	std::map<IDPlayer, EloScore> res = ea->calculateEloScore(clas);

	ASSERT_EQ(comp, res);
}

TEST_F(EloTestFixure, EloAlgorithmMuchDiffEloPlayersWin2) {
	std::shared_ptr<Team> t1 = std::make_shared<Team>(0);
	std::shared_ptr<Team> t2 = std::make_shared<Team>(1);

	std::vector<std::shared_ptr<Team> > vt1;
	std::vector<std::shared_ptr<Team> > vt2;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(0);
	p1->setElo(0);
	t1->addPlayerInTeam(p1);
	t1->addEloTeam(p1->getElo());
	vt1.emplace_back(t1);

	std::shared_ptr<Player> p2 = std::make_shared<Player>(1);
	p2->setElo(400);
	t2->addPlayerInTeam(p2);
	t2->addEloTeam(p2->getElo());
	vt2.emplace_back(t2);

	std::shared_ptr<Classification> clas = std::make_shared<Classification>();
	clas->addResult(1, vt2);
	clas->addResult(2, vt1);

	std::map<IDPlayer, EloScore> comp;
	pair<IDPlayer, EloScore> pa1(0, -4);
	comp.emplace(pa1);
	pair<IDPlayer, EloScore> pa2(1, 4);
	comp.emplace(pa2);

	std::shared_ptr<EloAlgorithm> ea = std::make_shared<EloAlgorithm>(m_L);
	std::map<IDPlayer, EloScore> res = ea->calculateEloScore(clas);

	ASSERT_EQ(comp, res);
}