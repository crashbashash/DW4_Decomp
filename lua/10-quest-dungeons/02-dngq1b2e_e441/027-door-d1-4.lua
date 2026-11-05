if be:FLGisOn(134) ~= 1 and be:FLGisOn(133) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON", 30)
    be:FLGset(130, 1)
end
be:sd("MODELCTRL", "g_d1door", 4, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
be:FLGset(112, 1)
