if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    g_matg09 = 1
    if be:FLGisOn(125) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-03", 1)
