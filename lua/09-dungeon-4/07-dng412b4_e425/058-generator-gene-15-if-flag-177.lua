if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(177) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
end
