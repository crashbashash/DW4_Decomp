if be:MDLgetRamNo() == 0 then
    be:FLGset(138, 1)
    for local_1 = 0, 2 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(139, 1)
    for local_1 = 3, 12 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(140, 1)
    if be:FLGisOn(143) ~= 1 then
        for local_1 = 13, 22 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(141, 1)
    if be:FLGisOn(131) ~= 1 then
        for local_1 = 23, 29 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 4 then
    be:FLGset(142, 1)
    for local_1 = 30, 41 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 5 and be:FLGisOn(42, be:FLGisOn(), be, 140) ~= 1 then
    for local_1 = 13, 22 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
