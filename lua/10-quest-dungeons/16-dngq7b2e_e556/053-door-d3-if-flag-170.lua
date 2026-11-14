if be:MATisAllPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    if be:FLGisOn(170) ~= 1 then
        if g_door04 ~= 1 then
            be:sd("MODELCTRL", "g_d3door", 3, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall04", 0, "ONHIT")
            g_door04 = 1
        end
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
end
