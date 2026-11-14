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
    if be:FLGisOn(130) ~= 1 then
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_THEME/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "QS_THEME", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-50,10,-890>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-70,10,-890>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,-900>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-90,10,-900>/V<0,180,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
        be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d2door", 8, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-11", 90)
        be:DMsetSD("MODELCTRL", "i_bosshp13", 0, "GENERATE", "V<0,205,0>/SQ_OPEN", 90)
        be:DMsetSD("METERCTRL", "bshp13", 0, "SETMODELHP", "e_anomalo/I<0>", 100)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
