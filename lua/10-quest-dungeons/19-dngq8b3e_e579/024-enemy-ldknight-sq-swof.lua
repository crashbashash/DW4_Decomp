if be:MATisAllPlayer() == 1 then
    local local_0
    local total = 0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
        end
    end
    if total == 0 then
        return
    end
    if be:FLGisOn(208) ~= 1 then
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_THEME/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "QS_THEME", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<670,10,-610>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<650,10,-610>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<690,10,-620>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<630,10,-620>/V<0,180,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
        be:DMsetSD("HITLANDMODEL", "doorwall22", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d4door", 21, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-22", 90)
        be:DMsetSD("ENEMY", "e_ldknight", 0, "OFCTRL", 100)
        be:DMsetSD("ENEMY", "e_ldknight", 0, "ONCTRL", 120)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp17", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp17", 0, "SETMODELHP", "e_ldknight/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
