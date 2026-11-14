local local_0
be:FLGset(177, 1)
be:sd("MODELCTRL", "g_d3door", 11, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
if be:FLGisOn(248) ~= 1 then
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
