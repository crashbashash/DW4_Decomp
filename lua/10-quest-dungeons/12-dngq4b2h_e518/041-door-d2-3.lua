if be:MATisPlayer() == 1 and be:FLGisOn(127) ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall04", 0, "ONHIT")
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
end
