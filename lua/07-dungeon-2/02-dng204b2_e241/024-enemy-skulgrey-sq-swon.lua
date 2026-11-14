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
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_skulgrey", 0, "MOVETRANS", "V<520,10,460>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<450,10,470>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<450,10,450>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<460,10,490>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<460,10,430>/V<0,90,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
be:DMsetSD("MODELCTRL", "g_d2door", 14, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 385)
be:DMsetSD("MODELCTRL", "g_d2door", 15, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall16", 0, "OFFHIT", 385)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE2", 60)
be:DMrun()
be:FLGset(140, 1)
if be:SYSgetDifficulty() > 0 then
    be:FLGset(601, 1)
end
