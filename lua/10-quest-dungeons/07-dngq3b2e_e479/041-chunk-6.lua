if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    if be:FLGisOn(125) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    elseif be:FLGisOn(126) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-04", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
