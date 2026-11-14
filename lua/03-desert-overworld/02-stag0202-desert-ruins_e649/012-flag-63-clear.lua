local local_0
local total = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
    end
end
if total ~= 0 then
    if g_IFLG08 ~= 1 then
        g_IFLG08 = 1
    elseif g_IFLG08 == 1 then
        be:sd("MODELCTRL", "g_lift03z02", 0, "SQ_SWON", 60)
        be:sd("MODELCTRL", "g_lift03az02", 0, "SQ_SWON")
        be:sd("MODELCTRL", "g_lift03bz02", 0, "SQ_SWON")
        be:sd("HITLANDMODEL", "hitlift030", 0, "OFFHIT", 180)
        be:sd("MODELCTRL", "g_lift04z02", 0, "SQ_SWON", 60)
        be:sd("HITLANDMODEL", "hitlift040", 0, "OFFHIT", 180)
        be:sd("MODELCTRL", "g_lift01z02", 2, "SQ_SWON", 60)
        be:sd("HITLANDMODEL", "hitlift012", 0, "OFFHIT", 180)
        be:FLGset(63, 0)
        if be:FLGisOn(368) == 0 then
            be:FLGset(368, 1)
        elseif be:FLGisOn(369) == 0 and be:FLGisOn(368) == 1 then
            be:FLGset(369, 1)
        elseif be:FLGisOn(370) == 0 and be:FLGisOn(369) == 1 and be:FLGisOn(368) == 1 then
            be:FLGset(370, 1)
        end
    end
else
end
