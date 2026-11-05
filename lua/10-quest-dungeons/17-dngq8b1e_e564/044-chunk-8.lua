if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    if be:FLGisOn(114) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
