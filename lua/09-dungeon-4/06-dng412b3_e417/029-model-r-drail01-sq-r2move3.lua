if g_r02mode == 0 then
    if be:SYSgetRandom(20) == 0 then
        be:sd("MODELCTRL", "r_drail01", 1, "SQ_R2MOVE3", 0)
        g_r02mode = 2
    else
        if be:SYSgetRandom(2) == 0 then
            be:sd("MODELCTRL", "r_drail01", 1, "SQ_R0MOVE1", 0)
        else
            be:sd("MODELCTRL", "r_drail01", 1, "SQ_R0MOVE2", 0)
        end
        g_r02mode = 1
    end
end
