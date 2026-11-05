if be:MDLgetRamNo() == 1 then
    be:FLGset(139, 1)
    for local_1 = 4, 7 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 0 then
    be:FLGset(140, 1)
    for local_1 = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
