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
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(107, 1)
    for local_1 = 24, 43 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
