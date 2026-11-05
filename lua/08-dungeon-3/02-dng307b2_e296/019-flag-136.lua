if be:MDLgetRamNo() == 0 then
    be:FLGset(136, 1)
    if be:FLGisOn(116) == 0 then
        be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
    else
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(137, 1)
    if be:FLGisOn(118) == 0 then
        be:sd("MODELCTRL", "g_dcap", 1, "SQ_DDMG")
    else
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(138, 1)
    for local_1 = 2, 7 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
