if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(128) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
end
