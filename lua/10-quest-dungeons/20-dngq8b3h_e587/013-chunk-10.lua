if be:MATisAllPlayer() == 1 and be:FLGisOn(202) ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
end
