if be:MDLgetRamNo() == 0 and be:FLGisOn(177) ~= 1 then
    for local_0 = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", local_0, "SQ_DDMG")
    end
end
