if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(115) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    end
end
