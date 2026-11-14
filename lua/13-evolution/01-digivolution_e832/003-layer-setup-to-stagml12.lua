be:sd("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
local local_0 = function(infoName, infoName2, ramNo)
    be:DMsetSD("MODELCTRL", "g_changebg", ramNo, "SQ_OPEN", 30)
    be:DMsetSD("MODELCTRL", infoName, ramNo, "SQ_ENTR", 30)
    be:DMchkSD("MODELCTRL", infoName, ramNo, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", infoName, ramNo, "ISSEQNAME", "SQ_ENTR", "==0")
    be:DMchkSD("MODELCTRL", infoName, ramNo, "ISSEQNAME", "SQ_ENTR", "!=0")
    be:DMsetSD("MODELCTRL", infoName, ramNo, "SQ_ERAS")
    be:DMsetSD("MODELCTRL", "i_evoline", ramNo, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "g_dchange", ramNo, "SQ_ACT2", 15)
    be:DMchkSD("MODELCTRL", "g_dchange", ramNo, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "g_dchange", ramNo, "ISSEQNAME", "SQ_ACT2", "==0")
    be:DMchkSD("MODELCTRL", "g_dchange", ramNo, "ISSEQNAME", "SQ_ACT2", "!=0")
    be:DMsetSD("MODELCTRL", "i_evowipe", ramNo, "GENERATE", "SQ_WTOUT00/V<0.0,0.0,0.0>/V<0,0,0>")
    be:DMchkSD("MODELCTRL", "i_evowipe", ramNo, "ISRUN", "==0")
    be:DMsetSD("MODELCTRL", "g_dchange", ramNo, "SQ_ERAS")
    be:DMsetSD("MODELCTRL", "g_changebg", ramNo, "SQ_ERAS")
    be:DMsetSD("MODELCTRL", "g_changebg2", ramNo, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
    be:DMsetSD("MODELCTRL", "i_evowipe", ramNo, "SQ_WTIN20")
    be:DMchkSD("MODELCTRL", "i_evowipe", ramNo, "ISSEQNAME", "SQ_WTIN20", "==0")
    be:DMchkSD("MODELCTRL", "i_evowipe", ramNo, "ISSEQNAME", "SQ_WTIN20", "!=0")
    be:DMsetSD("MODELCTRL", infoName2, ramNo, "SQ_ENJOY")
    be:DMchkSD("MODELCTRL", infoName2, ramNo, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", infoName2, ramNo, "ISSEQNAME", "SQ_ENJOY", "==0")
    be:DMsetSD("MODELCTRL", "g_changebg2", ramNo, "ONFREEZE", 80)
    be:DMchkSD("MODELCTRL", infoName2, ramNo, "ISSEQNAME", "SQ_ENJOY", "!=0")
end
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
    local local_1
    local count = 0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if playerIndex == 0 then
                if g_oldNameP1 ~= g_nowNameP1 then
                    local_0(g_oldNameP1, g_nowNameP1, 0)
                    count = count + 1
                    if count > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                else
                end
            elseif playerIndex == 1 then
                if g_oldNameP2 ~= g_nowNameP2 then
                    local_0(g_oldNameP2, g_nowNameP2, 1)
                    count = count + 1
                    if count > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                else
                end
            elseif playerIndex == 2 then
                if g_oldNameP3 ~= g_nowNameP3 then
                    local_0(g_oldNameP3, g_nowNameP3, 2)
                    count = count + 1
                    if count > 1 then
                        be:DMrun()
                    else
                        be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                        be:DMrun()
                    end
                else
                end
            elseif playerIndex == 3 and g_oldNameP4 ~= g_nowNameP4 then
                local_0(g_oldNameP4, g_nowNameP4, 3)
                count = count + 1
                if count > 1 then
                    be:DMrun()
                else
                    be:DMsetSD("MODELCTRL", "i_evowipe", 4, "GENERATE", "SQ_BLOUT20/V<0.0,0.0,0.0>/V<0,0,0>", 90)
                    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 120)
                    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 120)
                    be:DMrun()
                end
            end
        elseif playerIndex == 0 then
        elseif playerIndex == 1 then
        elseif playerIndex == 2 then
        elseif playerIndex == 3 then
        end
    end
end
funcFirstLayerSet()
