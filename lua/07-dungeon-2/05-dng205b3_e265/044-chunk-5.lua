if be:MATisPlayer() == 1 then
    if be:FLGisOn(177) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03")
    end
    if be:FLGisOn(190) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16")
    end
    if be:FLGisOn(191) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17")
    end
    if be:FLGisOn(192) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18")
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-03")
be:sd("GENERATER", nil, -1, "STOP", "GENE-16")
be:sd("GENERATER", nil, -1, "STOP", "GENE-17")
be:sd("GENERATER", nil, -1, "STOP", "GENE-18")
