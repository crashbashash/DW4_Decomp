if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-10")
    be:FLGset(114, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-10")
end
