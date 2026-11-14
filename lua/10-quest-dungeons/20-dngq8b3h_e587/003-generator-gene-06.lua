if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(192) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
end
