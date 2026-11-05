if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_dfirefloor", 2, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_dfirefloor", 2, "SETLABEL", "SQ_WAIT/OFF")
end
