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
be:DMsetSD("MODELCTRL", "e_tonogeko", 0, "MOVETRANS", "V<-200,10,300>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-130,10,290>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-130,10,310>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-140,10,270>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-140,10,330>/V<0,-90,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
be:DMsetSD("MODELCTRL", "g_d3door", 6, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 385)
be:DMsetSD("MODELCTRL", "g_d3door", 7, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 385)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE3", 60)
be:DMrun()
be:FLGset(124, 1)
if be:SYSgetDifficulty() > 0 then
    be:FLGset(604, 1)
end
