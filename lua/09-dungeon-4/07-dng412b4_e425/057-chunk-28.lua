if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(176) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
