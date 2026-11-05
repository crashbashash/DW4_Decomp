if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
