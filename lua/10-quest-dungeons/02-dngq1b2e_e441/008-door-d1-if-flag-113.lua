if be:MATisAllPlayer() == 1 and be:FLGisOn(113) ~= 1 then
    if g_door05 ~= 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
        g_door05 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-04")
end
