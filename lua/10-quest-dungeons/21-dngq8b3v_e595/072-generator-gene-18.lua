if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    if be:FLGisOn(204) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    end
end
