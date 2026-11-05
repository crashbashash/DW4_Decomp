if be:MATisAllPlayer() == 1 then
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
        end
    end
    if local_1 == 0 then
        return nil, 0
    end
    if be:FLGisOn(189) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE2/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE2", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-50,10,230>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-70,10,230>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,220>/V<0,180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-90,10,220>/V<0,180,0>")
        be:DMsetSD("ENEMY", "e_pharaoh", -1, "SQ_ERAS")
        be:DMsetSD("ENEMY", "e_mummy", -1, "SQ_ERAS")
        be:DMsetSD("ENEMY", "e_mecha1", -1, "SQ_ERAS")
        be:DMsetSD("ENEMY", "e_mecha2", -1, "SQ_ERAS")
        be:DMsetSD("HITLANDMODEL", "doorwall22", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d2door", 21, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-15", 90)
        be:DMchkSD("MODELCTRL", "e_anomalo", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_anomalo", -1, "OFCTRL")
        mswk63008 = "DMINFOFONT01/font00/I<10>"
        mswk63009 = "DMINFOFONT02/font00/I<11>"
        mswk63010 = "DMINFOFONT02/font01/I<12>"
        mswk63011 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63008, mswk63009, mswk63010, mswk63011, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_anomalo", 0, "ONCTRL", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp13", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp13", 0, "SETMODELHP", "e_anomalo/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
