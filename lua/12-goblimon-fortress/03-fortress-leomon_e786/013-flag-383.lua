for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if be:FLGisOn(383) == 0 and local_1 ~= 0 then
    be:sd("MODELCTRL", "g_liftz05", 0, "SQ_SWON", 60)
    be:sd("HITLANDMODEL", "hitliftz05", 0, "OFFHIT", 180)
    be:FLGset(383, 1)
end
