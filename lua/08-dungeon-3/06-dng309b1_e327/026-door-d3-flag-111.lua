local local_0
be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
be:FLGset(111, 1)
if be:FLGisOn(126) then
    for ramNo = 0, 14 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG", 30)
    end
end
