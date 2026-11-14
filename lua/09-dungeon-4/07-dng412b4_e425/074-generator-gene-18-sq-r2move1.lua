if g_r02mode == 0 then
    if be:SYSgetRandom(20) == 0 then
        g_r02station = be:SYSgetRandom(3) + 1
        if g_r02station == 1 then
            be:sd("MODELCTRL", "r_drail02", 1, "SQ_R2MOVE1", 0)
        elseif g_r02station == 2 then
            be:sd("MODELCTRL", "r_drail02", 1, "SQ_R2MOVE2", 0)
        else
            be:sd("MODELCTRL", "r_drail02", 1, "SQ_R2MOVE3", 0)
        end
        g_r02mode = 2
    else
        if be:SYSgetRandom(2) == 0 then
            be:sd("MODELCTRL", "r_drail02", 1, "SQ_R0MOVE1", 0)
        else
            be:sd("MODELCTRL", "r_drail02", 1, "SQ_R0MOVE2", 0)
        end
        g_r02mode = 1
    end
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
end
