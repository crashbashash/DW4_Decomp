local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(185, 1)
    be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(186, 1)
    for ramNo = 33, 37 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
