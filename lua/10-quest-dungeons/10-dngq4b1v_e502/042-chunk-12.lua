if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "SETLABEL", "SQ_WAIT/ON")
    be:sd("MODELCTRL", "g_ddamagefloor", 9, "SETLABEL", "SQ_WAIT/ON")
    be:sd("MODELCTRL", "g_ddamagefloor", 10, "SETLABEL", "SQ_WAIT/ON")
else
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "SETLABEL", "SQ_WAIT/OFF")
    be:sd("MODELCTRL", "g_ddamagefloor", 9, "SETLABEL", "SQ_WAIT/OFF")
    be:sd("MODELCTRL", "g_ddamagefloor", 10, "SETLABEL", "SQ_WAIT/OFF")
end
