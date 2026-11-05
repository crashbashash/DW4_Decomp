if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
end
if be:FLGisOn(204) + be:FLGisOn(205) == 2 and be:MATisPlayer(be:FLGisOn(), be, 188) ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
else
end
if be:MATisAllPlayer() == 1 then
    be:sd("HITLANDMODEL", "safewall2", 0, "OFFHIT")
else
    be:sd("HITLANDMODEL", "safewall2", 0, "ONHIT")
end
