if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    if be:FLGisOn(134) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
end
