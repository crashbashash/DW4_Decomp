if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_dlasergun", 5, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_dlasergun", 5, "SETLABEL", "SQ_WAIT/OFF")
end
