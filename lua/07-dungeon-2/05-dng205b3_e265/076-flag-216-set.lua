local ramNo
if be:MDLgetRamNo() == 0 then
    be:FLGset(216, 1)
    for ramNo2 = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(217, 1)
    for ramNo2 = 11, 12 do
        be:sd("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(218, 1)
    for ramNo2 = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(219, 1)
    ramNo = 13
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
