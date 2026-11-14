if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(181) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-19", 1)
end
