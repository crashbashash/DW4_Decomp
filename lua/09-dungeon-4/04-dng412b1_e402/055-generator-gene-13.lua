if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(223) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
end
