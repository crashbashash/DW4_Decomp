if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(222) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-12", 1)
