if not g_f_devl1Pos then
    g_f_devl1Pos = 0
end
g_act = 1
g_Poschk[g_f_devl1Pos] = 0
local_1 = be:SYSgetRandom(6)
if g_f_devl1Pos == local_1 and local_1 > 5 then
    local_1 = 0
end
if local_1 == 0 then
    local_0 = "V<-148.67,10.0,24.0>/V<0.0,90.0,0.0>"
elseif local_1 == 1 then
    local_0 = "V<-148.67,10.0,-25.0>/V<0.0,90.0,0.0>"
elseif local_1 == 2 then
    local_0 = "V<-24.21,10.0,-150.0>/V<0.0,0.0,0.0>"
elseif local_1 == 3 then
    local_0 = "V<26.87,10.0,-150.0>/V<0.0,0.0,0.0>"
elseif local_1 == 4 then
    local_0 = "V<146.36,10.0,-25.0>/V<0.0,-90.0,0.0>"
elseif local_1 == 5 then
    local_0 = "V<146.36,10.0,24.0>/V<0.0,-90.0,0.0>"
end
be:sd("MODELCTRL", "f_devl1", 0, "MOVETRANS", local_0)
if be:MDLisCallName("out") == 1 then
    g_devlDmgChk = 0
    for local_4 = 0, 2 do
        if be:MDLisLive("e_mecha4bs", local_4) == 1 then
            local_3 = 1
        end
    end
    if g_devl1blive == 0 and local_3 == 0 then
        be:sd("MODELCTRL", "f_devl1", 0, "SQ_WARPOUT", 30)
    else
        be:sd("MODELCTRL", "f_devl1", 0, "SQ_WARPOUT1", 30)
    end
elseif be:MDLisCallName("out1") == 1 then
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_WARPOUT2", 60)
end
g_Poschk[local_1] = 1
g_f_devl1Pos = local_1
