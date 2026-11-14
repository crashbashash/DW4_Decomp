local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(170, 1)
    for ramNo = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(171, 1)
    for ramNo = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
