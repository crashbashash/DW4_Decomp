be:FLGset(177, 1)
be:sd("MODELCTRL", "g_d3door", 11, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
if be:FLGisOn(248) ~= 1 then
    for local_1 = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
