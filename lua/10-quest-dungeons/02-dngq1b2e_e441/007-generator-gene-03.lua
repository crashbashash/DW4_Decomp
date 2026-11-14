if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
end
