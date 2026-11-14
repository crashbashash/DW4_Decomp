if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "SETLABEL", "SQ_WAIT/ON")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "SETLABEL", "SQ_WAIT/OFF")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "SETLABEL", "SQ_WAIT/OFF")
end
