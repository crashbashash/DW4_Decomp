if be:MATisPlayer() == 1 then
    if g_pharaoh02 ~= 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE")
        be:sd("GENERATER", nil, -1, "START", "GENE-02")
        g_pharaoh02 = 1
    end
    be:MATsetRun(0)
end
