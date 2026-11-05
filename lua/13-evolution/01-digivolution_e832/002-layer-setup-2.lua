be:FLGset(364, 0)
funcStartLayerSet()
be:sd("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT00/V<0.0,0.0,0.0>/V<0,0,0>")
g_joincount = 0
for local_0 = 0, 3 do
    if be:SYSisJoinPlayer(local_0) == 1 then
        g_joincount = g_joincount + 1
    end
end
if g_joincount == 1 then
    be:sd("MODELCTRL", "g_changebg", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", "i_evoline", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dchange", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", g_oldNameP1, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", g_nowNameP1, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
elseif g_evocount == 1 then
    be:sd("MODELCTRL", "g_changebg", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", "i_evoline", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dchange", 4, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    if g_oldNameP1 ~= g_nowNameP1 then
        be:sd("MODELCTRL", g_oldNameP1, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
        be:sd("MODELCTRL", g_nowNameP1, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
    elseif g_oldNameP2 ~= g_nowNameP2 then
        be:sd("MODELCTRL", g_oldNameP2, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
        be:sd("MODELCTRL", g_nowNameP2, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
    elseif g_oldNameP3 ~= g_nowNameP3 then
        be:sd("MODELCTRL", g_oldNameP3, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
        be:sd("MODELCTRL", g_nowNameP3, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
    elseif g_oldNameP4 ~= g_nowNameP4 then
        be:sd("MODELCTRL", g_oldNameP4, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
        be:sd("MODELCTRL", g_nowNameP4, 4, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
    else
    end
end
for local_0 = 0, 3 do
    if be:SYSisJoinPlayer(local_0) == 1 then
        if local_0 == 0 then
            if g_oldNameP1 ~= g_nowNameP1 then
                be:sd("MODELCTRL", "g_changebg", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "i_evoline", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "g_dchange", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_oldNameP1, 0, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_nowNameP1, 0, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
            else
                be:sd("MODELCTRL", "i_evoclose", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
            end
        end
        if local_0 == 1 then
            if g_oldNameP2 ~= g_nowNameP2 then
                be:sd("MODELCTRL", "g_changebg", 1, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "i_evoline", 1, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "g_dchange", 1, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_oldNameP2, 1, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_nowNameP2, 1, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
            else
                be:sd("MODELCTRL", "i_evoclose", 1, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
            end
        end
        if local_0 == 2 then
            if g_oldNameP3 ~= g_nowNameP3 then
                be:sd("MODELCTRL", "g_changebg", 2, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "i_evoline", 2, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "g_dchange", 2, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_oldNameP3, 2, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_nowNameP3, 2, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
            else
                be:sd("MODELCTRL", "i_evoclose", 2, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
            end
        end
        if local_0 == 3 then
            if g_oldNameP4 ~= g_nowNameP4 then
                be:sd("MODELCTRL", "g_changebg", 3, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "i_evoline", 3, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", "g_dchange", 3, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_oldNameP4, 3, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
                be:sd("MODELCTRL", g_nowNameP4, 3, "GENERATE", "SQ_HIDE/V<0.0,0.0,0.0>/V<0,0,0>")
            else
                be:sd("MODELCTRL", "i_evoclose", 3, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
            end
        end
    end
    if local_0 == 0 then
        be:sd("MODELCTRL", "i_evoclose", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    elseif local_0 == 1 then
        be:sd("MODELCTRL", "i_evoclose", 1, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    elseif local_0 == 2 then
        be:sd("MODELCTRL", "i_evoclose", 2, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    elseif local_0 == 3 then
        be:sd("MODELCTRL", "i_evoclose", 3, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    end
end
