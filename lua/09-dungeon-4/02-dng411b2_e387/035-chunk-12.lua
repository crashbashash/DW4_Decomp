if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(125) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
