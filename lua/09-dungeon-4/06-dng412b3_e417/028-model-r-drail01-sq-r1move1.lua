if g_r01mode == 0 then
    if be:SYSgetRandom(2) == 0 then
        be:sd("MODELCTRL", "r_drail01", 0, "SQ_R1MOVE1", 0)
    else
        be:sd("MODELCTRL", "r_drail01", 0, "SQ_R1MOVE2", 0)
    end
    g_r01mode = 1
end
