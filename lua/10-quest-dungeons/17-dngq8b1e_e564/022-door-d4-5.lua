be:FLGset(120, 1)
if be:FLGisOn(141) ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 14, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
    be:FLGset(141, 1)
end
if be:FLGisOn(142) ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 15, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT", 45)
    be:FLGset(142, 1)
end
be:sd("MODELCTRL", "g_d4door", 16, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT", 45)
