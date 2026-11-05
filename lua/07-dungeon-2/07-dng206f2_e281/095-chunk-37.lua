if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(151) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-20", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-20", 1)
