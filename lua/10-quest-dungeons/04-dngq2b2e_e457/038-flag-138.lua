if be:MDLgetRamNo() == 0 then
    be:FLGset(138, 1)
    for local_1 = 0, 2 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(139, 1)
    for local_1 = 3, 12 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
