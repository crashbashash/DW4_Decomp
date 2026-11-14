if be:FLGisOn(120) == 1 then
    if be:FLGisOn(122) == 1 then
        be:sd("MODELCTRL", "g_d4door", 10, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
    else
        be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    end
end
be:FLGset(121, 1)
