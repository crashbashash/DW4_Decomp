if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(163) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-20", 1)
    end
end
