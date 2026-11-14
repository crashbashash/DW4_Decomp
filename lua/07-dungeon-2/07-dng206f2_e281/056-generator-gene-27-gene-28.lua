if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(158) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-27", 1)
    end
    if be:FLGisOn(159) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-28", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-27", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-28", 1)
end
