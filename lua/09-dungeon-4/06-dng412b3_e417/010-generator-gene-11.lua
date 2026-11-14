if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(110) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
end
