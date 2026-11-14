if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if be:FLGisOn(166) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
end
