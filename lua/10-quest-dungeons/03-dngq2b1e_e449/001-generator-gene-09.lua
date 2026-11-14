if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
end
