if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    if be:FLGisOn(120) ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTOF")
        be:sd("HITLANDMODEL", "doorwall15", 0, "ONHIT")
        be:sd("MODELCTRL", "g_d4door", 15, "SQ_SILENTON")
        be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    end
    if be:FLGisOn(118) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
end
