local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(163, 1)
    for ramNo = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(164, 1)
    if be:FLGisOn(165) ~= 1 then
        for ramNo = 8, 10 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(165, 1)
    if be:FLGisOn(164) ~= 1 then
        for ramNo = 8, 10 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
