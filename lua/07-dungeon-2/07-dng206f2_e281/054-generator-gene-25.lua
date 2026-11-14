if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-27")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-28")
    if be:FLGisOn(156) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-25", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-25", 1)
end
