if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
