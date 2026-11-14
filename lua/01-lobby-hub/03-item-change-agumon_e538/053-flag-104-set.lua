local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(104, 1)
    if be:FLGisOn(102) ~= 1 then
        for ramNo = 0, 1 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(105, 1)
    if be:FLGisOn(103) ~= 1 then
        for ramNo = 2, 3 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(106, 1)
    for ramNo = 4, 23 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
    be:sd("MODELCTRL", "g_dcap", 74, "SQ_DDMG")
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(107, 1)
    for ramNo = 24, 43 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 4 then
    be:FLGset(108, 1)
    for ramNo = 75, 115 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 5 then
    be:FLGset(109, 1)
    for ramNo = 116, 117 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 6 then
    be:FLGset(110, 1)
    for ramNo = 118, 161 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
