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
    if be:FLGisOn(119) ~= 1 then
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DG_CAVE1/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DG_CAVE1", 31)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_SBOSS", 32)
        be:DMchkSD("SOUND", nil, -1, "ISREADY", "BT_SBOSS", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossbefore")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<570,10,-230>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<570,10,-250>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<580,10,-210>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<580,10,-270>/V<0,90,0>")
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
        be:DMsetSD("MODELCTRL", "g_d1door", 4, "SQ_SWOF")
        be:DMsetSD("HITLANDMODEL", "doorwall05", 0, "ONHIT")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_SBOSS", 60)
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-08", 90)
        be:DMchkSD("MODELCTRL", "e_blosso", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_blosso", -1, "OFCTRL")
        mswk63092 = "DMINFOFONT01/font00/I<14>"
        mswk63093 = "DMINFOFONT02/font00/I<15>"
        mswk63094 = "DMINFOFONT02/font01/I<16>"
        mswk63095 = "DMINFOFONT02/font02/I<17>"
        funcOpenDigimonInfoWin(mswk63092, mswk63093, mswk63094, mswk63095, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("MODELCTRL", "e_blosso", 0, "ONCTRL", 210)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "i_bosshp10", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
        be:DMsetSD("METERCTRL", "bshp10", 0, "SETMODELHP", "e_blosso/I<0>", 10)
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
    be:MATsetRun(0)
end
