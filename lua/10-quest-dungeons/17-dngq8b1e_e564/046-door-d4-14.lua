if be:MATisPlayer() == 1 and be:FLGisOn(116) ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall13", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-17")
end
