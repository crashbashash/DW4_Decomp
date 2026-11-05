if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(156) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
