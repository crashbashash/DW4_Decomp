if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    if be:FLGisOn(147) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
end
