if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(141) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
