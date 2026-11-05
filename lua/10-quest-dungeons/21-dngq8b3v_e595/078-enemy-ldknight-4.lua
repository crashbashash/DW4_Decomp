if be:MATisAllPlayer() == 1 then
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
        end
    end
    if local_1 == 0 then
        return nil, 0
    end
    if be:FLGisOn(251) ~= 1 then
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_THEME/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "QS_THEME", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore3", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<670,10,-1010>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<650,10,-1010>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<690,10,-1020>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<630,10,-1020>/V<0,180,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
        be:DMsetSD("HITLANDMODEL", "doorwall24", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d4door", 23, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-24", 90)
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
