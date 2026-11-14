if be:MATisAllPlayer() == 1 and be:FLGisOn(143) ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall03", 0, "ONHIT")
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWON", 15)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 30)
    be:FLGset(143, 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(104) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
end
