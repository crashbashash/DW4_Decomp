if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-08")
    be:FLGset(112, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08")
end
