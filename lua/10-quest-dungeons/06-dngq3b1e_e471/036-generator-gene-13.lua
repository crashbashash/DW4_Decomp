if be:SYSgetDifficulty() > 0 and be:MATisPlayer() == 1 and be:FLGisOn(121) == 1 and be:FLGisOn(112) ~= 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
end
