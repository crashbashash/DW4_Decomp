if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(104) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
end
