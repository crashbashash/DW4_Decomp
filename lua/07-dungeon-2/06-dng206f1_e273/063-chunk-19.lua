if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("MODELCTRL", "g_dfirefloor", 0, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_dfirefloor", 0, "SETLABEL", "SQ_WAIT/OFF")
end
