if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(147) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
end
