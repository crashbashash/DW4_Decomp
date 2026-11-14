if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(133) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
end
