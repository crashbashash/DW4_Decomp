if be:MDLgetRamNo() == 0 then
    be:FLGset(177, 1)
    if be:FLGisOn(180) ~= 1 then
        for local_0 = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(178, 1)
    if be:FLGisOn(186) ~= 1 then
        for local_0 = 8, 12 do
            be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(179, 1)
    if be:FLGisOn(186) ~= 1 then
        for local_0 = 13, 18 do
            be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 3 and be:FLGisOn(177) ~= 1 then
    for local_0 = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
    end
end
