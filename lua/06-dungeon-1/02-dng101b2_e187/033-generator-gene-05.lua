if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    if be:FLGisOn(116) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
end
