if be:MATisPlayer() == 1 and be:FLGisOn(187) ~= 1 then
    for local_1 = 1, 20 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
    be:FLGset(187, 1)
end
