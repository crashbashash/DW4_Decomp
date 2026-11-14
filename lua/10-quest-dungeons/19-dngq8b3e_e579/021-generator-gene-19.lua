if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    if be:FLGisOn(205) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
end
