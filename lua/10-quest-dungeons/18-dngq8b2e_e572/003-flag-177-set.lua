if be:MDLgetRamNo() == 0 then
    be:FLGset(177, 1)
    if be:FLGisOn(180) ~= 1 then
        for ramNo = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(178, 1)
    if be:FLGisOn(186) ~= 1 then
        for ramNo = 8, 12 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(179, 1)
    if be:FLGisOn(186) ~= 1 then
        for ramNo = 13, 18 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(180, 1)
    if be:FLGisOn(177) ~= 1 then
        for ramNo = 0, 7 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
