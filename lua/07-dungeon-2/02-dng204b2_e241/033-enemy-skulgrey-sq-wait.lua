if be:MDLisLive("x_015factn06a", 0) == 1 and be:MDLisLive("x_015factn06a", 1) == 1 then
    be:sd("MODELCTRL", "e_skulgrey", 0, "SQ_WAIT", 0)
else
    be:sd("MODELCTRL", "e_skulgrey", 0, "SQ_ATMAP", 0)
end
