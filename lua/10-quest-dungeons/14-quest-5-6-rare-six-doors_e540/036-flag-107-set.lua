if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-03")
    be:FLGset(107, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-03")
end
