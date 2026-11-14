if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-07")
    be:FLGset(111, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07")
end
