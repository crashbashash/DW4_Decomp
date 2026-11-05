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
be:DMsetSD("MODELCTRL", "e_anomalo", 0, "MOVETRANS", "V<-60,10,160>/V<0,0,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-50,10,230>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-70,10,230>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,220>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-90,10,220>/V<0,180,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
be:DMsetSD("MODELCTRL", "g_d2door", 21, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall22", 0, "OFFHIT", 385)
be:DMsetSD("MODELCTRL", "g_d2door", 22, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall23", 0, "OFFHIT", 385)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE2", 60)
be:DMrun()
be:FLGset(189, 1)
if be:SYSgetDifficulty() > 0 then
    be:FLGset(602, 1)
end
