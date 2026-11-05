if be:MATisPlayer() == 1 then
    if be:FLGisOn(142) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10")
    end
    if be:FLGisOn(148) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16")
    end
    if be:FLGisOn(149) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17")
    end
    if be:FLGisOn(150) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18")
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-10")
be:sd("GENERATER", nil, -1, "STOP", "GENE-16")
be:sd("GENERATER", nil, -1, "STOP", "GENE-17")
be:sd("GENERATER", nil, -1, "STOP", "GENE-18")
