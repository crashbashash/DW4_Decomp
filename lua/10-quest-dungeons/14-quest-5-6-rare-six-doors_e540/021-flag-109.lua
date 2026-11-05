if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-05")
    be:FLGset(109, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-05")
end
