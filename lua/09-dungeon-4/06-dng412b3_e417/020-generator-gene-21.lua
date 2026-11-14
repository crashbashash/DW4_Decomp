if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-21", 1)
    end
end
