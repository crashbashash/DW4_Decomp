if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    if be:FLGisOn(180) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-18", 1)
