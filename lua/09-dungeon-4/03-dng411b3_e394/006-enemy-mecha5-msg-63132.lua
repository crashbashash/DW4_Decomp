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
    if be:FLGisOn(156) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE4/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE4", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-150,10,270>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-150,10,250>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-140,10,290>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-140,10,230>/V<0,90,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
        be:DMsetSD("HITLANDMODEL", "doorwall18", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d4door", 17, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-23", 90)
        be:DMchkSD("MODELCTRL", "e_mecha5", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_mecha5", -1, "OFCTRL")
        mswk63132 = "DMINFOFONT01/font00/I<14>"
        mswk63133 = "DMINFOFONT02/font00/I<15>"
        mswk63134 = "DMINFOFONT02/font01/I<16>"
        mswk63135 = "DMINFOFONT02/font02/I<17>"
        funcOpenDigimonInfoWin(mswk63132, mswk63133, mswk63134, mswk63135, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_mecha5", 0, "ONCTRL", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp16", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp16", 0, "SETMODELHP", "e_mecha5/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
