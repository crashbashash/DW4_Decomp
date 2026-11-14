if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-11")
    be:FLGset(115, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-11")
end
