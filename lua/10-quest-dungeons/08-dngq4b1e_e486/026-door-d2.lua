if be:FLGisOn(111) ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:FLGset(111, 1)
end
if be:FLGisOn(112) ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    be:FLGset(112, 1)
end
be:FLGset(106, 1)
