local local_0
local total = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
    end
end
if total ~= 0 then
    be:sd("HITLANDMODEL", "hitbrossgatez010", 0, "OFFHIT", 25)
    be:sd("HITLANDMODEL", "hitbrossgatez011", 0, "OFFHIT", 25)
    be:sd("MODELCTRL", "g_brossgatez01", 0, "SQ_SWOF")
    be:sd("MODELCTRL", "g_brossgatez01", 1, "SQ_SWOF")
    be:FLGset(66, 1)
end
