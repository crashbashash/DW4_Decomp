local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(152, 1)
    for ramNo = 18, 48 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(153, 1)
    for ramNo = 67, 79 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(154, 1)
    for ramNo = 80, 87 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(155, 1)
    for ramNo = 67, 79 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
