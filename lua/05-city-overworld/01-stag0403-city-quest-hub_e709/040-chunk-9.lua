if be:MATisPlayer() == 1 then
    if g_lFLG03 ~= 1 then
        be:sd("MODELCTRL", "g_minez04", 8, "GENERATE", "V<335,60,-75>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 9, "GENERATE", "V<285,60,-75>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 10, "GENERATE", "V<335,60,85>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 11, "GENERATE", "V<285,60,85>/V<0,0,0>")
        g_lFLG03 = 1
    end
    be:sd("MODELCTRL", "g_minez04", 8, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 9, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 10, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 11, "SQ_POWERON", 10)
elseif be:MATisPlayer() == 0 then
    be:sd("MODELCTRL", "g_minez04", 8, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 9, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 10, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 11, "SQ_POWEROF", 10)
end
