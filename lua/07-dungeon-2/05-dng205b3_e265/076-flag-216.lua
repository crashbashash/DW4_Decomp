if be:MDLgetRamNo() == 0 then
    be:FLGset(216, 1)
    for local_1 = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(217, 1)
    for local_1 = 11, 12 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(218, 1)
    for local_1 = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(219, 1)
    local_0 = 13
    be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
end
