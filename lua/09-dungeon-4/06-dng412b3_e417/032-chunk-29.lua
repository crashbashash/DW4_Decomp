if g_r04mode == 0 then
    if be:SYSgetRandom(20) == 0 then
        be:sd("MODELCTRL", "r_drail01", 3, "SQ_R4MOVE3", 0)
        g_r04mode = 2
    else
        if be:SYSgetRandom(2) == 0 then
            be:sd("MODELCTRL", "r_drail01", 3, "SQ_R0MOVE1", 0)
        else
            be:sd("MODELCTRL", "r_drail01", 3, "SQ_R0MOVE2", 0)
        end
        g_r04mode = 1
    end
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
end
