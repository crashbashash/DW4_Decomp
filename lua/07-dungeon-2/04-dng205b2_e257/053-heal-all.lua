funcHealGate("ALL", "g_dallhealeffect", 0)
local local_0
for playerIndex = 0, 3 do
    if be:MATisRidePlayer(playerIndex) == 1 then
        be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "CLEARMETAL")
    end
    if be:MATisRideOffPlayer(playerIndex) == 1 then
        be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SETMETAL")
    end
end
