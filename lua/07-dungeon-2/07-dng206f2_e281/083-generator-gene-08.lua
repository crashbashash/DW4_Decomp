if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(139) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
end
