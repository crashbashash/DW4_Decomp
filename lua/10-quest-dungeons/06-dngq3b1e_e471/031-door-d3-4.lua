if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:MATisAllPlayer() == 1 and be:FLGisOn(106) ~= 1 then
        if be:FLGisOn(121) ~= 1 then
            if be:FLGisOn(139) ~= 1 then
                be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWOF")
                be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
                be:FLGset(139, 1)
            else
            end
        end
        if be:FLGisOn(140) ~= 1 then
            be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
            be:FLGset(140, 1)
        end
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
