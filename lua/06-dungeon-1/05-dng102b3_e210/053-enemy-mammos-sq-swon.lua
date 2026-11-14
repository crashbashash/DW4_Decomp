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
be:DMsetSD("MODELCTRL", "e_mammos", 0, "MOVETRANS", "V<-660,10,120>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-590,10,130>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-590,10,110>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-600,10,150>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-600,10,90>/V<0,-90,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
be:DMsetSD("MODELCTRL", "g_d1door", 8, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 385)
be:DMsetSD("MODELCTRL", "g_d1door", 9, "SQ_SWON", 370)
be:DMsetSD("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 385)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE1", 60)
be:DMrun()
be:FLGset(150, 1)
be:FLGset(508, 0)
if be:SYSgetDifficulty() > 0 then
    be:FLGset(599, 1)
end
