if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(165) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    end
end
