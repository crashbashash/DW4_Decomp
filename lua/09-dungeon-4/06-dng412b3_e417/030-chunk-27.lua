if g_r03mode == 0 then
    if be:SYSgetRandom(20) == 0 then
        be:sd("MODELCTRL", "r_drail01", 2, "SQ_R3MOVE3", 0)
        g_r03mode = 2
    else
        if be:SYSgetRandom(2) == 0 then
            be:sd("MODELCTRL", "r_drail01", 2, "SQ_R3MOVE1", 0)
        else
            be:sd("MODELCTRL", "r_drail01", 2, "SQ_R3MOVE2", 0)
        end
        g_r03mode = 1
    end
end
