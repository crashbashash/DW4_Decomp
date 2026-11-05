if be:MDLgetRamNo() == 0 then
    be:FLGset(185, 1)
    be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(186, 1)
    for local_1 = 33, 37 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
