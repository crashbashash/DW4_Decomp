g_mecha4live = g_mecha4live + -1
g_devl1blive = g_devl1blive + 1
if g_UFOPos == 0 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-01")
elseif g_UFOPos == 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-02")
elseif g_UFOPos == 2 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-03")
elseif g_UFOPos == 3 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-04")
end
