if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "SETLABEL", "SQ_WAIT/ON")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "SETLABEL", "SQ_WAIT/OFF")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "SETLABEL", "SQ_WAIT/OFF")
end
