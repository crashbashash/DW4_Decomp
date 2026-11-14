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
    if be:FLGisOn(124) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE3/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE3", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-130,10,290>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-130,10,310>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-140,10,270>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-140,10,330>/V<0,-90,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
        be:DMsetSD("HITLANDMODEL", "doorwall07", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d3door", 6, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-11", 90)
        be:DMchkSD("MODELCTRL", "e_tonogeko", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_tonogeko", -1, "OFCTRL")
        mswk63080 = "DMINFOFONT01/font00/I<10>"
        mswk63081 = "DMINFOFONT02/font00/I<11>"
        mswk63082 = "DMINFOFONT02/font01/I<12>"
        mswk63083 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63080, mswk63081, mswk63082, mswk63083, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_tonogeko", 0, "ONCTRL", 210)
        be:DMsetSD("MODELCTRL", "e_tonogeko", 0, "SQ_SWON", 211)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp14", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp14", 0, "SETMODELHP", "e_tonogeko/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
