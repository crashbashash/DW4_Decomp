local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(136, 1)
    if be:FLGisOn(116) == 0 then
        be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(137, 1)
    if be:FLGisOn(118) == 0 then
        be:sd("MODELCTRL", "g_dcap", 1, "SQ_DDMG")
    end
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(138, 1)
    for ramNo = 2, 7 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
