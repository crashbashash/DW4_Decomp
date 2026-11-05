if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(115) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
