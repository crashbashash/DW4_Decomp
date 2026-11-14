if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(120) ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTON")
        be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d4door", 15, "SQ_SILENTOF")
        be:sd("HITLANDMODEL", "doorwall16", 0, "ONHIT")
    end
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
end
