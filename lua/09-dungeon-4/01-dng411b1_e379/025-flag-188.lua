if be:FLGisOn(188) ~= 1 then
    be:FLGset(188, 1)
    for local_1 = 0, 4 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
