local local_0
local total = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
    end
end
if be:FLGisOn(383) == 0 and total ~= 0 then
    be:sd("MODELCTRL", "g_liftz05", 0, "SQ_SWON", 60)
    be:sd("HITLANDMODEL", "hitliftz05", 0, "OFFHIT", 180)
    be:FLGset(383, 1)
end
