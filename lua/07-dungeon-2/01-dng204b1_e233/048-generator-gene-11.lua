if be:MATisPlayer() == 1 then
    if be:FLGisOn(110) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11")
    else
        be:MATsetRun(0)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-11")
end
