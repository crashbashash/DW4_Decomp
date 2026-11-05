if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(153) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    elseif be:FLGisOn(154) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
