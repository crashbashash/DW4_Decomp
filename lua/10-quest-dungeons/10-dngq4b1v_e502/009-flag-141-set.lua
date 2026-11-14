if be:MDLgetRamNo() == 0 then
    be:FLGset(141, 1)
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(142, 1)
    if be:FLGisOn(141) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(143, 1)
    if be:FLGisOn(144) ~= 1 and be:FLGisOn(145) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 1, "SQ_DDMG")
        be:sd("MODELCTRL", "g_dcap", 2, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(144, 1)
    if be:FLGisOn(143) ~= 1 and be:FLGisOn(145) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 1, "SQ_DDMG")
        be:sd("MODELCTRL", "g_dcap", 2, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 4 then
    be:FLGset(145, 1)
    if be:FLGisOn(143) ~= 1 and be:FLGisOn(144) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 1, "SQ_DDMG")
        be:sd("MODELCTRL", "g_dcap", 2, "SQ_DDMG")
    end
end
