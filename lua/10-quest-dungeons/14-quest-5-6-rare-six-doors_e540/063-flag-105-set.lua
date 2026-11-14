if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-01")
    be:FLGset(105, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01")
end
