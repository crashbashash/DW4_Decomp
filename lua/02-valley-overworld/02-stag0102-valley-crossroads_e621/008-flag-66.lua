for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 ~= 0 then
    be:sd("HITLANDMODEL", "hitbrossgatez010", 0, "OFFHIT", 25)
    be:sd("HITLANDMODEL", "hitbrossgatez011", 0, "OFFHIT", 25)
    be:sd("MODELCTRL", "g_brossgatez01", 0, "SQ_SWOF")
    be:sd("MODELCTRL", "g_brossgatez01", 1, "SQ_SWOF")
    be:FLGset(66, 1)
end
