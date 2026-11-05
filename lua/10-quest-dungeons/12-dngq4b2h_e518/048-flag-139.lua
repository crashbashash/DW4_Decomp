if be:MDLgetRamNo() == 0 then
    be:FLGset(139, 1)
    for local_1 = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(140, 1)
    be:sd("MODELCTRL", "g_dcap", 4, "SQ_DDMG")
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(143, 1)
    for local_1 = 5, 11 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(144, 1)
    for local_1 = 12, 17 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
