if be:MDLgetRamNo() == 0 then
    be:FLGset(139, 1)
    if be:FLGisOn(146) ~= 1 and be:FLGisOn(147) ~= 1 then
        for local_1 = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(140, 1)
    if be:FLGisOn(149) ~= 1 then
        for local_1 = 8, 16 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(146, 1)
    if be:FLGisOn(139) ~= 1 and be:FLGisOn(147) ~= 1 then
        for local_1 = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    if be:FLGisOn(148) ~= 1 then
        for local_1 = 17, 22 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(147, 1)
    if be:FLGisOn(139) ~= 1 and be:FLGisOn(146) ~= 1 then
        for local_1 = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    if be:FLGisOn(149) ~= 1 and be:FLGisOn(150) ~= 1 then
        for local_1 = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 4 then
    be:FLGset(148, 1)
    if be:FLGisOn(146) ~= 1 then
        for local_1 = 17, 22 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    if be:FLGisOn(150) ~= 1 then
        for local_1 = 31, 39 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 5 then
    be:FLGset(149, 1)
    if be:FLGisOn(140) ~= 1 then
        for local_1 = 8, 16 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    if be:FLGisOn(147) ~= 1 and be:FLGisOn(150) ~= 1 then
        for local_1 = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 6 then
    be:FLGset(150, 1)
    if be:FLGisOn(147) ~= 1 and be:FLGisOn(149) ~= 1 then
        for local_1 = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    if be:FLGisOn(148) ~= 1 then
        for local_1 = 31, 39 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 7 then
    be:FLGset(151, 1)
    for local_1 = 40, 50 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
