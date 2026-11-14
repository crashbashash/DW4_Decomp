local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(117, 1)
    for ramNo = 0, 10 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(118, 1)
    if be:FLGisOn(119) ~= 1 then
        for ramNo = 11, 33 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(119, 1)
    if be:FLGisOn(118) ~= 1 then
        for ramNo = 11, 33 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
