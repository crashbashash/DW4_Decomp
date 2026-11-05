if be:MDLgetRamNo() == 0 then
    be:FLGset(170, 1)
    for local_1 = 0, 7 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(171, 1)
    for local_1 = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
