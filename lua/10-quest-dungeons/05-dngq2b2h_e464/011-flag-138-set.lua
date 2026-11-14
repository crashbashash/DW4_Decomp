local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(138, 1)
    for ramNo = 0, 2 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(139, 1)
    for ramNo = 3, 12 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(140, 1)
    if be:FLGisOn(143) ~= 1 then
        for ramNo = 13, 22 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(141, 1)
    if be:FLGisOn(131) ~= 1 then
        for ramNo = 23, 29 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 4 then
    be:FLGset(142, 1)
    for ramNo = 30, 41 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 5 then
    be:FLGset(143, 1)
    if be:FLGisOn(129) ~= 1 then
        for ramNo = 42, 46 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
    if be:FLGisOn(140) ~= 1 then
        for ramNo = 13, 22 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
