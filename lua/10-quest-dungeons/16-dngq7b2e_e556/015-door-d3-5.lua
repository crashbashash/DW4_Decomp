be:FLGset(172, 1)
if be:FLGisOn(171) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
end
