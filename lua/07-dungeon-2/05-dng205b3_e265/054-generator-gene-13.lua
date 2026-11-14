if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(187) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
end
