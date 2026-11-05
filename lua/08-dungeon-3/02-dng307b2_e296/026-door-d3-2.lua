be:sd("MODELCTRL", "g_d3door", 1, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
be:FLGset(116, 1)
if be:FLGisOn(136) == 0 then
    be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG", 30)
end
