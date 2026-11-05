if be:MDLgetRamNo() == 0 then
    be:FLGset(163, 1)
    for local_1 = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(164, 1)
    if be:FLGisOn(165) ~= 1 then
        for local_1 = 8, 10 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 2 and be:FLGisOn(164) ~= 1 then
    for local_1 = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
