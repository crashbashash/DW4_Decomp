if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("MODELCTRL", "g_dlasergun", 2, "SETLABEL", "SQ_WAIT/ON")
    be:sd("MODELCTRL", "g_dlasergun", 3, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_dlasergun", 2, "SETLABEL", "SQ_WAIT/OFF")
    be:sd("MODELCTRL", "g_dlasergun", 3, "SETLABEL", "SQ_WAIT/OFF")
end
