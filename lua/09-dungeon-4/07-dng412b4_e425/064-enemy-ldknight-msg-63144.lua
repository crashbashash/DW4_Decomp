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
    if be:FLGisOn(183) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE4/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE4", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-190,100,-810>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-210,100,-810>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-170,100,-820>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-230,100,-820>/V<0,180,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
        be:DMsetSD("HITLANDMODEL", "doorwall14", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d4door", 13, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-21", 90)
        be:DMchkSD("MODELCTRL", "e_ldknight", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_ldknight", -1, "OFCTRL")
        mswk63144 = "DMINFOFONT01/font00/I<10>"
        mswk63145 = "DMINFOFONT02/font00/I<11>"
        mswk63146 = "DMINFOFONT02/font01/I<12>"
        mswk63147 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63144, mswk63145, mswk63146, mswk63147, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_ldknight", 0, "ONCTRL", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp17", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp17", 0, "SETMODELHP", "e_ldknight/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
