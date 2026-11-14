if be:MATisPlayer() == 1 then
    g_pcOnMatG01 = 1
    if be:FLGisOn(127) == 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01")
    else
        be:MATsetRun(0)
    end
else
    g_pcOnMatG01 = 0
    if g_pcOnMatG02 ~= 1 then
        be:sd("GENERATER", nil, -1, "STOP", "GENE-01")
    end
end
