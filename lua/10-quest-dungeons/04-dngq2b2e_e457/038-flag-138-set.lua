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
