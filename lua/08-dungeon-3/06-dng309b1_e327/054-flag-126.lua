be:FLGset(126, 1)
if be:FLGisOn(111) then
    for local_1 = 0, 14 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
