local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(139, 1)
    if be:FLGisOn(146) ~= 1 and be:FLGisOn(147) ~= 1 then
        for ramNo = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(140, 1)
    if be:FLGisOn(149) ~= 1 then
        for ramNo = 8, 16 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(146, 1)
    if be:FLGisOn(139) ~= 1 and be:FLGisOn(147) ~= 1 then
        for ramNo = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(148) ~= 1 then
        for ramNo = 17, 22 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(147, 1)
    if be:FLGisOn(139) ~= 1 and be:FLGisOn(146) ~= 1 then
        for ramNo = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(149) ~= 1 and be:FLGisOn(150) ~= 1 then
        for ramNo = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 4 then
    be:FLGset(148, 1)
    if be:FLGisOn(146) ~= 1 then
        for ramNo = 17, 22 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(150) ~= 1 then
        for ramNo = 31, 39 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 5 then
    be:FLGset(149, 1)
    if be:FLGisOn(140) ~= 1 then
        for ramNo = 8, 16 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(147) ~= 1 and be:FLGisOn(150) ~= 1 then
        for ramNo = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 6 then
    be:FLGset(150, 1)
    if be:FLGisOn(147) ~= 1 and be:FLGisOn(149) ~= 1 then
        for ramNo = 23, 30 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(148) ~= 1 then
        for ramNo = 31, 39 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 7 then
    be:FLGset(151, 1)
    for ramNo = 40, 50 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
