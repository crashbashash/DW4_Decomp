if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    if be:FLGisOn(109) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
end
