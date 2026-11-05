be:sd("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "DM_EVOLV")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "AM_EVOLV")
be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "DM_EVOLV")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "AM_EVOLV", 25)
be:DMrun()
be:sd("MODELCTRL", "i_evowipe", 4, "SQ_BLIN20", 5)
if g_joincount == 1 then
    local_0(g_oldNameP1, g_nowNameP1, 4)
    be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
    be:DMrun()
elseif g_evocount == 1 then
    if g_oldNameP1 ~= g_nowNameP1 then
        local_0(g_oldNameP1, g_nowNameP1, 4)
    elseif g_oldNameP2 ~= g_nowNameP2 then
        local_0(g_oldNameP2, g_nowNameP2, 4)
    elseif g_oldNameP3 ~= g_nowNameP3 then
        local_0(g_oldNameP3, g_nowNameP3, 4)
    elseif g_oldNameP4 ~= g_nowNameP4 then
        local_0(g_oldNameP4, g_nowNameP4, 4)
    end
    be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
    be:DMrun()
else
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 then
            if local_3 == 0 then
                if g_oldNameP1 ~= g_nowNameP1 then
                    local_0(g_oldNameP1, g_nowNameP1, 0)
                    local_2 = local_2 + 1
                    if local_2 > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                end
            end
            if local_3 == 1 then
                if g_oldNameP2 ~= g_nowNameP2 then
                    local_0(g_oldNameP2, g_nowNameP2, 1)
                    local_2 = local_2 + 1
                    if local_2 > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                end
            end
            if local_3 == 2 then
                if g_oldNameP3 ~= g_nowNameP3 then
                    local_0(g_oldNameP3, g_nowNameP3, 2)
                    local_2 = local_2 + 1
                    if local_2 > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                end
            end
            if local_3 == 3 and g_oldNameP4 ~= g_nowNameP4 then
                local_0(g_oldNameP4, g_nowNameP4, 3)
                local_2 = local_2 + 1
                if local_2 > 1 then
                    be:DMrun()
                else
                    be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                    be:DMrun()
                end
            end
        end
        if local_3 == 0 then
        elseif local_3 == 1 then
        elseif local_3 == 2 then
        elseif local_3 == 3 then
        end
    end
end
funcFirstLayerSet()
