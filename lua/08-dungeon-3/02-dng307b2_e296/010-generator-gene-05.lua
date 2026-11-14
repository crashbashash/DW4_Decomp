if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(118) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
end
