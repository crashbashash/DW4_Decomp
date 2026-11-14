if be:MATisAllPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-00")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-01")
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-00")
    be:sd("GENERATER", nil, -1, "STOP", "GENE-01")
end
