if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(179) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-17", 1)
end
