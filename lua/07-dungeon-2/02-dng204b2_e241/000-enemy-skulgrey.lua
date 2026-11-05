if be:MATisAllPlayer() == 1 then
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
        end
    end
    if local_1 == 0 then
        return nil, 0
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE2/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE2", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<450,10,470>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<450,10,450>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<460,10,490>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<460,10,430>/V<0,90,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
        be:DMsetSD("HITLANDMODEL", "doorwall15", 0, "ONHIT")
        be:DMsetSD("MODELCTRL", "g_d2door", 14, "SQ_SWOF")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-13", 90)
        be:DMchkSD("MODELCTRL", "e_skulgrey", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_skulgrey", -1, "OFCTRL")
        mswk63052 = "DMINFOFONT01/font00/I<14>"
        mswk63053 = "DMINFOFONT02/font00/I<15>"
        mswk63054 = "DMINFOFONT02/font01/I<16>"
        mswk63055 = "DMINFOFONT02/font02/I<17>"
        funcOpenDigimonInfoWin(mswk63052, mswk63053, mswk63054, mswk63055, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_skulgrey", 0, "ONCTRL", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp12", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp12", 0, "SETMODELHP", "e_skulgrey/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
