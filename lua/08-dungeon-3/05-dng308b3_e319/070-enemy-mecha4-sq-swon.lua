g_bossRest = g_bossRest + -1
if g_bossRest == 0 then
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
    be:DMsetSD("MODELCTRL", "e_mecha4", be:MDLgetRamNo(), "MOVETRANS", "V<-680,10,-400>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-670,10,-330>/V<0,180,0>")
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-690,10,-330>/V<0,180,0>")
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-650,10,-340>/V<0,180,0>")
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-710,10,-340>/V<0,180,0>")
    be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
    be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
    be:DMsetSD("MODELCTRL", "g_d3door", 7, "SQ_SWON", 370)
    be:DMsetSD("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 385)
    be:DMsetSD("MODELCTRL", "g_d3door", 8, "SQ_SWON", 370)
    be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 385)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
    be:DMsetSD("SOUND", nil, -1, "PLAY", "DG_CAVE3", 60)
    be:DMrun()
    be:FLGset(157, 1)
    if be:SYSgetDifficulty() > 0 then
        be:FLGset(605, 1)
    end
end
