if be:FLGisOn(137) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-06", 1)
else
    be:FLGset(125, 1)
end
