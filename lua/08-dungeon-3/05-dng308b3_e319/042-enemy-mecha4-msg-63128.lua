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
    if be:FLGisOn(157) ~= 1 then
        g_bossRest = 3
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE3/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE3", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-670,10,-330>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-690,10,-330>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-650,10,-340>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-710,10,-340>/V<0,180,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
        be:DMsetSD("HITLANDMODEL", "doorwall08", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d3door", 7, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-19", 90)
        be:DMchkSD("MODELCTRL", "e_mecha4", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_mecha4", -1, "OFCTRL")
        mswk63128 = "DMINFOFONT01/font00/I<10>"
        mswk63129 = "DMINFOFONT02/font00/I<11>"
        mswk63130 = "DMINFOFONT02/font01/I<12>"
        mswk63131 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63128, mswk63129, mswk63130, mswk63131, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("MODELCTRL", "e_mecha4", -1, "ONCTRL")
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
