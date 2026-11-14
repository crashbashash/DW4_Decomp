if be:FLGisOn(139) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(139, 0)
end
if be:FLGisOn(140) == 1 then
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(140, 0)
end
be:FLGset(106, 1)
