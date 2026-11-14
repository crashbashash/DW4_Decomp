if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-04", 1)
end
