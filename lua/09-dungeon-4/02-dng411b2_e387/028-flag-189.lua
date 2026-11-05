if be:MATisPlayer() == 1 and be:FLGisOn(189) ~= 1 then
    for local_1 = 2, 5 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
    be:FLGset(189, 1)
end
