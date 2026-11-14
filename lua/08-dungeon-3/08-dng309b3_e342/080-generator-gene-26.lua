if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(182) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-26", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-26", 1)
end
