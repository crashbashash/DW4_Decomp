if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if be:FLGisOn(100) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01")
    elseif be:FLGisOn(101) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02")
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-01")
be:sd("GENERATER", nil, -1, "STOP", "GENE-02")
