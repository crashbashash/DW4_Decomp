if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(134) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
end
