if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(107) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
end
