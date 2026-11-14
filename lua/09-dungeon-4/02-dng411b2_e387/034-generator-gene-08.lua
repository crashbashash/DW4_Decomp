if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(124) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
end
