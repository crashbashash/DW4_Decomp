if be:MATisAllPlayer() == 1 and be:FLGisOn(112) ~= 1 then
    if g_door12 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 11, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall12", 0, "ONHIT")
        g_door12 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-13")
end
