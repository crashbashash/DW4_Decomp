if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(151) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
end
