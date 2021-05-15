--[[
function puntuationTeam ()
	local res = math.random(1, 100)
	return res
end
--]]

function playMatch(matchParticipants)
	matchTeams = {}
	for index, team in ipairs(matchParticipants) do
		local teamArmor = 0
		local teamStrength = 0
		teamProperties = {}
		teamProperties["teamPos"] = index
		for player, property in ipairs (team) do
			for key, value in pairs(property) do
				if key == "Strength" then
					teamStrength = teamStrength + value
				elseif key == "Armor" then
					teamArmor = teamArmor + value
				end
			end
		end
		teamProperties["Strength"] = teamStrength
		teamProperties["Armor"] = teamArmor
		matchTeams[index] = teamProperties
	end
	damageDealTeams = {}
	for index, team in ipairs(matchTeams) do
		local damage = 0
		for index2, team2 in ipairs(matchTeams) do
			if index ~= index2 then
				damage = damage + (team["Strength"] - team2["Armor"])
			end
		end
		damageDealTeams[index] = {index, damage}
	end
	table.sort(damageDealTeams, function (a, b)
		return a[2] > b[2]
	end)
	--[[
	for index3, team3 in ipairs(damageDealTeams) do
		print("pos table ", index3)
		for pos, dam in ipairs(team3) do
			print("pos ", pos, dam)
		end
	end
	--]]
	classification = {}
	for index, teamResults in ipairs(damageDealTeams) do
		classification[index] = {teamResults[1]}
		--print(teamResults[1])
	end
end

function getTableSize(t)
    local count = 0
    for _, __ in pairs(t) do
        count = count + 1
    end
    return count
end

function calculateEloScore(teamA, teamB)
	local deltaTeam = teamB - teamA
	local divElev = deltaTeam / 800
	local elev = math.pow(10, divElev)
	local res = (1/(1+elev))
	return res
end

playerProperties = {}

properties = {"ID", "Strength", "Armor"}

--matchParticipants = {}

classification = {}

--[[
prova = {{ ID = 0, Strength = 0, Armor = 19 },
	 { ID = 1, Strength = 1, Armor = 18 },
	 { ID = 2, Strength = 2, Armor = 17 },
	 { ID = 3, Strength = 3, Armor = 16 },
	 { ID = 4, Strength = 4, Armor = 15 },
	 { ID = 5, Strength = 5, Armor = 14 },
	 { ID = 6, Strength = 6, Armor = 13 },
	 { ID = 7, Strength = 7, Armor = 12 },
	 { ID = 8, Strength = 8, Armor = 11 },
	 { ID = 9, Strength = 9, Armor = 10 },
	 { ID = 10, Strength = 10, Armor = 9 },
	 { ID = 11, Strength = 11, Armor = 8 },
	 { ID = 12, Strength = 12, Armor = 7 },
	 { ID = 13, Strength = 13, Armor = 6 },
	 { ID = 14, Strength = 14, Armor = 5 },
	 { ID = 15, Strength = 15, Armor = 4 },
	 { ID = 16, Strength = 16, Armor = 3 },
	 { ID = 17, Strength = 17, Armor = 2 },
	 { ID = 18, Strength = 18, Armor = 1 },
	 { ID = 19, Strength = 19, Armor = 0 },
}
--]]

