if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(118) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
    if be:FLGisOn(119) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
end
