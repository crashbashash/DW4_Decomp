if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(110) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
