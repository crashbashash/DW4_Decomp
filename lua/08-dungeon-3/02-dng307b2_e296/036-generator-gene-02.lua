if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(115) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
end
