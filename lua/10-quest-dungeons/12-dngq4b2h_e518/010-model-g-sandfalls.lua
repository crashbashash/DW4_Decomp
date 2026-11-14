stageLocalFuncQuickSandOn("V<-220.0,10.0,-120.0>")
local local_0
if be:MATisPlayer() == 1 then
    local local_1
    local_0 = 0
    for playerIndex = 0, 3 do
        if be:MATisRidePlayer(playerIndex) ~= 0 then
            local_0 = 1
        end
    end
end
if local_0 == 1 then
    if be:MATisRidePlayer(0) ~= 0 then
        g_matRideL0 = 1
    end
    if be:MATisRidePlayer(1) ~= 0 then
        g_matRideL1 = 1
    end
    if be:MATisRidePlayer(2) ~= 0 then
        g_matRideL2 = 1
    end
    if be:MATisRidePlayer(3) ~= 0 then
        g_matRideL3 = 1
    end
    local local_1 = g_matRideS0 + g_matRideS1 + g_matRideS2 + g_matRideS3
    local local_2 = g_matRideM0 + g_matRideM1 + g_matRideM2 + g_matRideM3
    local local_3 = g_matRideL0 + g_matRideL1 + g_matRideL2 + g_matRideL3
    if local_1 ~= 0 then
        if g_nowSeq ~= 0 then
            be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGES")
            g_nowSeq = 0
        end
    elseif local_2 ~= 0 then
        if g_nowSeq ~= 1 then
            be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEM")
            g_nowSeq = 1
        end
    elseif local_3 ~= 0 then
        if g_nowSeq ~= 2 then
            be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEL")
            g_nowSeq = 2
        end
    elseif g_nowSeq ~= 3 then
        be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEX")
        g_nowSeq = 3
    end
elseif be:MATisRideOffPlayer(0) ~= 0 then
    g_matRideL0 = 0
end
if be:MATisRideOffPlayer(1) ~= 0 then
    g_matRideL1 = 0
end
if be:MATisRideOffPlayer(2) ~= 0 then
    g_matRideL2 = 0
end
if be:MATisRideOffPlayer(3) ~= 0 then
    g_matRideL3 = 0
end
local local_1 = g_matRideS0 + g_matRideS1 + g_matRideS2 + g_matRideS3
local local_2 = g_matRideM0 + g_matRideM1 + g_matRideM2 + g_matRideM3
local local_3 = g_matRideL0 + g_matRideL1 + g_matRideL2 + g_matRideL3
if local_1 ~= 0 then
    if g_nowSeq ~= 0 then
        be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGES")
        g_nowSeq = 0
    end
elseif local_2 ~= 0 then
    if g_nowSeq ~= 1 then
        be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEM")
        g_nowSeq = 1
    end
elseif local_3 ~= 0 then
    if g_nowSeq ~= 2 then
        be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEL")
        g_nowSeq = 2
    end
elseif g_nowSeq ~= 3 then
    be:sd("MODELCTRL", "g_sandfalls", 0, "SQ_RANGEX")
    g_nowSeq = 3
end
