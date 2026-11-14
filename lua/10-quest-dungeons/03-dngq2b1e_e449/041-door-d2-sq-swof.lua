if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(100) ~= 1 then
        if be:MATisAllPlayer() == 1 and g_gene01 ~= 1 then
            be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall01", 0, "ONHIT")
            be:sd("MODELCTRL", "g_d2door", 1, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall02", 0, "ONHIT")
            be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
            g_gene01 = 1
        end
    elseif be:FLGisOn(101) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
end
