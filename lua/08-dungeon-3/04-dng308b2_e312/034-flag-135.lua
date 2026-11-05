if be:MDLgetRamNo() == 0 then
    be:FLGset(135, 1)
    if g_dcap ~= 1 then
        for local_1 = 0, 11 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
        g_dcap = 1
    else
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(136, 1)
    be:sd("MODELCTRL", "g_dcap", 12, "SQ_DDMG")
end
