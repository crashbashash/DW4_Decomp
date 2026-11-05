if be:MDLgetRamNo() == 0 then
    be:sd("GENERATER", nil, -1, "STOP", "GENE-54")
    be:FLGset(349, 1)
elseif be:MDLgetRamNo() == 1 then
    be:sd("GENERATER", nil, -1, "STOP", "GENE-16")
    be:FLGset(350, 1)
elseif be:MDLgetRamNo() == 2 then
    be:sd("GENERATER", nil, -1, "STOP", "GENE-19")
    be:FLGset(351, 1)
end
