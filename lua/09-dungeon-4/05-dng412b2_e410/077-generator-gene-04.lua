if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(259) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-04", 1)
end
