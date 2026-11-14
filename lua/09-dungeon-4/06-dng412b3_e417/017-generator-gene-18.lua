if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    if be:FLGisOn(117) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-18", 1)
end
