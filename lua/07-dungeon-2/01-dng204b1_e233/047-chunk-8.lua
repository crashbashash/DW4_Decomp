if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(107) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    elseif be:FLGisOn(108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
