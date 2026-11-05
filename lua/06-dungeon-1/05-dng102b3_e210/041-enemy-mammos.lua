if be:MATisAllPlayer() == 1 then
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
        end
    end
    if local_1 == 0 then
        return nil, 0
    end
    if be:FLGisOn(150) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE1/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE1", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-590,10,130>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-590,10,110>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-600,10,150>/V<0,-90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-600,10,90>/V<0,-90,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
        be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d1door", 8, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-12", 90)
        be:DMchkSD("MODELCTRL", "e_mammos", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_mammos", -1, "OFCTRL")
        mswk63104 = "DMINFOFONT01/font00/I<10>"
        mswk63105 = "DMINFOFONT02/font00/I<11>"
        mswk63106 = "DMINFOFONT02/font01/I<12>"
        mswk63107 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63104, mswk63105, mswk63106, mswk63107, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("ENEMY", "e_mammos", 0, "ONCTRL", 150)
        be:DMsetSD("ENEMY", "e_mammos", 0, "SQ_WALKIN", 151)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp11", 0, "GENERATE", "V<0,205,0>/SQ_OPEN", 90)
        be:DMsetSD("METERCTRL", "bshp11", 0, "SETMODELHP", "e_mammos/I<0>", 100)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
