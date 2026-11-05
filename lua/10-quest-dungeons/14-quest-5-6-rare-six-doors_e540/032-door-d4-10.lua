if be:FLGisOn(120) + be:FLGisOn(121) == 2 then
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
else
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
end
be:FLGset(122, 1)
