if be:MATisPlayer() == 1 then
    if g_rolllaser01 ~= 1 then
        be:sd("MODELCTRL", "g_drolllaser", 0, "SQ_FIRE")
        g_rolllaser01 = 1
    else
    end
end
be:sd("MODELCTRL", "g_drolllaser", 0, "SQ_POWEROF")
g_rolllaser01 = 0
