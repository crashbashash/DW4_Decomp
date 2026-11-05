if be:MDLgetRamNo() == 0 and be:FLGisOn(104) ~= 1 then
    for local_1 = 0, 4 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
    be:FLGset(104, 1)
end
