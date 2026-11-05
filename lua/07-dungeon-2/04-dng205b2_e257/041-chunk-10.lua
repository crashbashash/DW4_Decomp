if be:MATisPlayer() == 1 then
    if g_pharaoh12 ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12")
        be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_FIRE")
        g_pharaoh12 = 1
    else
        be:MATsetRun(0)
    end
end
