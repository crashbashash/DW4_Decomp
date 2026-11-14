if be:SYSgetDifficulty() < 1 then
    be:MATsetRun(0)
    return
end
if be:MATisPlayer() == 1 then
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12")
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE")
    end
    be:MATsetRun(0)
end
