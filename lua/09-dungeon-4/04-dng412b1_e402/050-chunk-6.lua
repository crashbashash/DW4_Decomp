if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(217) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
