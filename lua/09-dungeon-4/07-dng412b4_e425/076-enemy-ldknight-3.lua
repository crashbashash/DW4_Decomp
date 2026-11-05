for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 == 0 then
    return nil, 0
end
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_ldknight", 0, "MOVETRANS", "V<-200,100,-880>/V<0,0,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-190,100,-810>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-210,100,-810>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-170,100,-820>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-230,100,-820>/V<0,180,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 300)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 340)
be:DMsetSD("MODELCTRL", "g_d4door", 13, "SQ_SWON", 470)
be:DMsetSD("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 485)
be:DMsetSD("MODELCTRL", "g_d4door", 14, "SQ_SWON", 470)
be:DMsetSD("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 485)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE4", 60)
be:DMrun()
be:FLGset(183, 1)
be:FLGset(83, 1)
if be:SYSgetDifficulty() > 0 then
    be:FLGset(609, 1)
end
