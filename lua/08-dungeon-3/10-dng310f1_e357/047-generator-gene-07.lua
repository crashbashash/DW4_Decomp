if be:MATisPlayer() == 1 then
    if be:FLGisOn(106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07")
    else
        be:MATsetRun(0)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07")
end
