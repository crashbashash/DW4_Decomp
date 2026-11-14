if be:MATisAllPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    if be:FLGisOn(171) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
end
