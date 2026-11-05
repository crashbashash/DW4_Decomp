if g_dmgfloor45 ~= 1 then
    if be:MATisPlayer() == 1 then
        be:sd("MODELCTRL", "g_ddamagefloor", 3, "SETLABEL", "SQ_WAIT/ON")
        be:sd("MODELCTRL", "g_ddamagefloor", 4, "SETLABEL", "SQ_WAIT/ON")
    else
        be:sd("MODELCTRL", "g_ddamagefloor", 3, "SETLABEL", "SQ_WAIT/OFF")
        be:sd("MODELCTRL", "g_ddamagefloor", 4, "SETLABEL", "SQ_WAIT/OFF")
    end
end
