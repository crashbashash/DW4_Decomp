if be:MATisPlayer() == 1 then
    if be:FLGisOn(160) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17")
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-17")
end
