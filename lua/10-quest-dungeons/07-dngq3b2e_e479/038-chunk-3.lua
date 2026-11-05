if be:FLGisOn(121) ~= 1 then
    if be:MATisPlayer() == 1 then
        if be:FLGisOn(123) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
        else
        end
    end
    be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
else
    if be:MATisPlayer() == 1 then
        if be:FLGisOn(122) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
        else
        end
    end
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
end
