if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(182) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-20", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-20", 1)
end
