local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(139, 1)
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(140, 1)
    be:sd("MODELCTRL", "g_dcap", 4, "SQ_DDMG")
elseif be:MDLgetRamNo() == 2 then
    be:FLGset(143, 1)
    for ramNo = 5, 11 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(144, 1)
    for ramNo = 12, 17 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
