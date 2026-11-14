if be:MDLisLive("x_035factn06a", 0) == 1 and be:MDLisLive("x_035factn06a", 1) == 1 and be:MDLisLive("x_035factn06a", 2) == 1 and be:MDLisLive("x_035factn06a", 0) == 1 then
    be:sd("MODELCTRL", "f_luce", 0, "SQ_WAIT", 0)
else
    be:sd("MODELCTRL", "f_luce", 0, "SQ_MISSILE", 0)
end
