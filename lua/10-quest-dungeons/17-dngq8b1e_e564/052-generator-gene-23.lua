if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(122) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-23", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-23", 1)
end
