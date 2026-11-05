be:FLGset(112, 1)
if be:FLGisOn(111) == 1 then
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
end
