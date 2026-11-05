if be:MATisPlayer() == 1 then
    if g_lFLG02 ~= 1 then
        be:sd("MODELCTRL", "g_minez04", 0, "GENERATE", "V<335,60,-75>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 1, "GENERATE", "V<285,60,-75>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 2, "GENERATE", "V<335,60,85>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 3, "GENERATE", "V<285,60,85>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 4, "GENERATE", "V<335,60,115>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 5, "GENERATE", "V<285,60,115>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 6, "GENERATE", "V<335,60,275>/V<0,0,0>")
        be:sd("MODELCTRL", "g_minez04", 7, "GENERATE", "V<285,60,275>/V<0,0,0>")
        g_lFLG02 = 1
    end
    be:sd("MODELCTRL", "g_minez04", 0, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 1, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 2, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 3, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 4, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 5, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 6, "SQ_POWERON", 10)
    be:sd("MODELCTRL", "g_minez04", 7, "SQ_POWERON", 10)
elseif be:MATisPlayer() == 0 then
    be:sd("MODELCTRL", "g_minez04", 0, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 1, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 2, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 3, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 4, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 5, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 6, "SQ_POWEROF", 10)
    be:sd("MODELCTRL", "g_minez04", 7, "SQ_POWEROF", 10)
end
