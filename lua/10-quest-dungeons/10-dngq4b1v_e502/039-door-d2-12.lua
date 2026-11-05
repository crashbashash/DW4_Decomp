if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall09", 0, "ONHIT")
        be:FLGset(111, 0)
    end
    if be:FLGisOn(112) == 1 then
        be:sd("MODELCTRL", "g_d2door", 9, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
        be:FLGset(112, 0)
    end
    be:sd("GENERATER", nil, -1, "RESET", "GENE-07")
    be:FLGset(106, 0)
end
