if g_r01mode == 0 then
    if be:SYSgetRandom(20) == 0 then
        g_r01station = be:SYSgetRandom(3) + 1
        if g_r01station == 1 then
            be:sd("MODELCTRL", "r_drail02", 0, "SQ_R1MOVE1", 0)
        elseif g_r01station == 2 then
            be:sd("MODELCTRL", "r_drail02", 0, "SQ_R1MOVE2", 0)
        else
            be:sd("MODELCTRL", "r_drail02", 0, "SQ_R1MOVE3", 0)
        end
        g_r01mode = 2
    else
        if be:SYSgetRandom(2) == 0 then
            be:sd("MODELCTRL", "r_drail02", 0, "SQ_R0MOVE1", 0)
        else
            be:sd("MODELCTRL", "r_drail02", 0, "SQ_R0MOVE2", 0)
        end
        g_r01mode = 1
    end
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
end
