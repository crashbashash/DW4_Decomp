if be:MATisPlayer() == 1 and be:FLGisOn(108) ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-09")
end
