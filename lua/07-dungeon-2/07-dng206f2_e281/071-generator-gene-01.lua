if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-27")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-28")
    if be:FLGisOn(132) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
end
