if be:MDLgetRamNo() == 0 then
    be:FLGset(117, 1)
    for local_1 = 0, 10 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(118, 1)
    if be:FLGisOn(119) ~= 1 then
        for local_1 = 11, 33 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 2 and be:FLGisOn(118) ~= 1 then
    for local_1 = 11, 33 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
