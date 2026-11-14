if be:MDLisCallName("en1") == 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-01")
elseif be:MDLisCallName("en2") == 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-02", 0)
elseif be:MDLisCallName("en3") == 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-03", 0)
end
