if be:MATisAllPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    if be:FLGisOn(173) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
end
