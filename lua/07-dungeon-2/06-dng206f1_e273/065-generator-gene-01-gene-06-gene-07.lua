if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("MODELCTRL", "g_dfirefloor", 2, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_dfirefloor", 2, "SETLABEL", "SQ_WAIT/OFF")
end
