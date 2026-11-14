if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-21", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-21", 1)
end
