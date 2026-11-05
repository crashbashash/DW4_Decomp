if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    if be:FLGisOn(137) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    elseif be:FLGisOn(138) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
