if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(159) == 1 and be:FLGisOn(141) == 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
end
