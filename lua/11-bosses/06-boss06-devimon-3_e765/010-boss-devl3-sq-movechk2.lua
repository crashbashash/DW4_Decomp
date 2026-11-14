if be:MDLisLive("f_devl3", 0) == 1 then
    if be:MATisPlayer() == 1 then
        be:sd("MODELCTRL", "f_devl3", 0, "SETLABEL", "SQ_MOVECHK2/move")
        be:sd("MODELCTRL", "f_devl3", 0, "SETLABEL", "SQ_MOVECHK1/move")
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SETLABEL", "SQ_MOVECHK2/stay")
    end
end
