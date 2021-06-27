--[[
function puntuationTeam ()
	local res = math.random(1, 100)
	return res
end
--]]

function initLua()
	math.randomseed(935)
end

k = 20

function gaussian (mean, variance)
    return  math.sqrt(-2 * variance * math.log(math.random())) *
            math.cos(2 * math.pi * math.random()) + mean
end

function playMatch(matchParticipants)
	local matchTeams = {}
	for index, team in ipairs(matchParticipants) do
		local teamArmor = 0
		local teamStrength = 0
		local teamProperties = {}
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
	local damageDealTeams = {}
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
	local classification = {}
	for index, teamResults in ipairs(damageDealTeams) do
		classification[index] = {teamResults[1]}
		--print(teamResults[1])
	end
	return classification
end

function getPlayerProperties(numPlayers)
	if next(playerProperties) == nil then
		for i = 1, numPlayers do
			local tablePlayer = {}
			--local var = 0
			for index, value in ipairs (properties) do
				if value == "ID" then
					local idValue = i - 1
					tablePlayer["ID"] = idValue
				elseif value == "Elo" then
					local elo = math.random(0, 1500)
					--local elo = 555
					tablePlayer["Elo"] = elo
				else
					--local valueTable = i + var
					local valueTable = gaussian(10, 9)
					if valueTable < 0 then
						valueTable = 0
					end
					tablePlayer[value] = valueTable
				end
				--var = var + 1
			end
			playerProperties[i] = tablePlayer
		end
	end
	return playerProperties
end

function getTableSize(t)
    local count = 0
    for _, __ in pairs(t) do
        count = count + 1
    end
    return count
end

function calculateChanceToWin(teamA, teamB)
	local deltaTeam = teamB - teamA
	local divElev = deltaTeam / 800
	local elev = math.pow(10, divElev)
	local res = (1/(1+elev))
	return res
end

function calculateEloScore(matchClassification)
	local k = 20
	local teamA = {}
	local teamB = {}
	local eloTeamA
	local eloTeamB
	local pos;
	local first = true
	local draw = false
	for key, value in pairs (matchClassification) do
		if key == "positionTeam" then
			pos = value
		else
			local size = getTableSize(value)
			if size > 2 then
				draw = true
			end
			for index, team in ipairs (value) do
				for key2, value2 in pairs (team) do
					if key2 == "eloTeam" then
						if first == true then
							eloTeamA = value2
						else
							eloTeamB = value2
						end
					else
						for index3, player in ipairs (value2) do
							for key3, value3 in pairs (player) do
								if key3 == "idPlayer" then
									if first == true then
										table.insert(teamA, value3)
									else
										table.insert(teamB, value3)
									end
								end
							end
						end
					end
					if eloTeamA ~= nil then
							first = false
					end
				end
			end
		end
	end	
	local deltaEloA
	local deltaEloB
	if draw then
		local eloA = k/2 * (1-calculateChanceToWin(eloTeamA, eloTeamB))
		local eloB = k/2 * (1-calculateChanceToWin(eloTeamB, eloTeamA))
		deltaEloA = eloA - eloB
		deltaEloB = eloB - eloA
	else
		deltaEloA = k * (1-calculateChanceToWin(eloTeamA, eloTeamB))
		deltaEloB = -deltaEloA
		--deltaEloA = k/4 * (1-calculateChanceToWin(eloTeamA, eloTeamB))
		--deltaEloB = -8*deltaEloA
	end
	local result = {}
	for indexA, idA in ipairs (teamA) do
		local changeEloPlayerA = {}
		changeEloPlayerA["idPlayer"] = idA
		changeEloPlayerA["deltaEloPlayer"] = deltaEloA
		table.insert(result,changeEloPlayerA)
	end
	for indexB, idB in ipairs (teamB) do
		local changeEloPlayerB = {}
		changeEloPlayerB["idPlayer"] = idB
		changeEloPlayerB["deltaEloPlayer"] = deltaEloB
		table.insert(result,changeEloPlayerB)
	end
	return result
end


playerProperties = {}

properties = {"ID", "Elo", "Strength", "Armor"}

--matchParticipants = {}

--classification = {}

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

