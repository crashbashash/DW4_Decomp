if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    if be:FLGisOn(141) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
