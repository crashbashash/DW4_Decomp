if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-06")
    be:FLGset(110, 1)
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-06")
end
