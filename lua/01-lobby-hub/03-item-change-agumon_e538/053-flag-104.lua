if be:MDLgetRamNo() == 0 then
    be:FLGset(104, 1)
    if be:FLGisOn(102) ~= 1 then
        for local_1 = 0, 1 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(105, 1)
    if be:FLGisOn(103) ~= 1 then
        for local_1 = 2, 3 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(106, 1)
    for local_1 = 4, 23 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
    be:sd("MODELCTRL", "g_dcap", 74, "SQ_DDMG")
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(107, 1)
    for local_1 = 24, 43 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 4 then
    be:FLGset(108, 1)
    for local_1 = 75, 115 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 5 then
    be:FLGset(109, 1)
    for local_1 = 116, 117 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 6 then
    be:FLGset(110, 1)
    for local_1 = 118, 161 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
