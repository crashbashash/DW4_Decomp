if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    if be:FLGisOn(151) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
