if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
end
