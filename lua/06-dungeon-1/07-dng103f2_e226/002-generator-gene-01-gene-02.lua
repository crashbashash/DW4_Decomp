if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(123) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    end
    if be:FLGisOn(124) ~= 1 and g_matg09 == 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
end
