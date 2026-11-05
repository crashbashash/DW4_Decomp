if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if be:FLGisOn(213) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
