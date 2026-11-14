if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(175) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
end
