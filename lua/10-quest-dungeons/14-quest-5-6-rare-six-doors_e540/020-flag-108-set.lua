if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-04")
    be:FLGset(108, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-04")
end
