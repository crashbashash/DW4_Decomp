if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-12")
    be:FLGset(116, 1)
    be:sd("GENERATER", nil, -1, "START", "GENE-13")
    be:FLGset(117, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOP", "GENE-13")
end
