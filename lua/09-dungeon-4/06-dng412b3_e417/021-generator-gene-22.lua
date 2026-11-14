if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    if be:FLGisOn(121) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-22", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-22", 1)
end
