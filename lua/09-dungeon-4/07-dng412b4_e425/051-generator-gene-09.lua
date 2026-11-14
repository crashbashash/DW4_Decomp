if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(171) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
end
