if be:MATisAllPlayer() == 1 and be:FLGisOn(212) ~= 1 then
    if g_door01 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 0, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall01", 0, "ONHIT")
        g_door01 = 1
    end
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
end
