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
	local classification = {}
	for index, teamResults in ipairs(damageDealTeams) do
		classification[index] = {teamResults[1]}
	end
	return classification
end

function getPlayerProperties(numPlayers)
	if next(playerProperties) == nil then
		for i = 1, numPlayers do
			local tablePlayer = {}
			for index, value in ipairs (properties) do
				if value == "ID" then
					local idValue = i - 1
					tablePlayer["ID"] = idValue
				elseif value == "Elo" then
					local elo = math.random(0, 1500)
					tablePlayer["Elo"] = elo
				else
					local valueTable = gaussian(10, 9)
					if valueTable < 0 then
						valueTable = 0
					end
					tablePlayer[value] = valueTable
				end
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
