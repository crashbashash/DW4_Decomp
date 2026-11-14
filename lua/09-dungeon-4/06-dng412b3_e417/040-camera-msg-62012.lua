local local_0
local ramNo = be:MDLgetRamNo()
be:DMsetSD("MODELCTRL", "r_drail01", ramNo, "ONFREEZE")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:sd("PLAYER", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
g_talk = "mess"
g_page = 0
g_messPlayerNo = 0
mswk62012 = "TALKFONT01/font01/I<10>"
mswk62013 = "TALKFONT01/font02/I<11>"
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
funcChoiceMessage(mswk62012, mswk62013)
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMswtSD("SELECTCTRL", "i_messcr", 0, "GETSELECT")
be:DMcase(0)
be:DMsetSD("PLAYER", nil, -1, "SQ_EXIT")
if ramNo == 1 then
    if g_r02mode == 2 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_go", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "SQ_R2DEMO2")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-715,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-705,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-695,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-685,40,-680>/V<0,0,0>")
        if be:FLGisOn(160) ~= 1 then
            for ramNo2 = 0, 17 do
                be:DMsetSD("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG", 300)
            end
        end
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 410)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "SQ_R0DEMO2")
    elseif g_r02mode == 3 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_back", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "SQ_R2DEMO3")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-475,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-465,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-455,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-445,40,-680>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 240)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail01", 1, "SQ_R2DEMO5")
    end
elseif ramNo == 2 then
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr03_go", 60)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("MODELCTRL", "r_drail01", 2, "SQ_R3DEMO2")
    be:DMsetSD("MODELCTRL", "r_drail01", 2, "OFFREEZE")
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<645,40,-120>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<655,40,-120>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<665,40,-120>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<675,40,-120>/V<0,0,0>")
    if be:FLGisOn(161) ~= 1 then
        for ramNo2 = 18, 48 do
            be:DMsetSD("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG", 410)
        end
    end
    be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 520)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("MODELCTRL", "r_drail01", 2, "SQ_R3DEMO4")
elseif ramNo == 3 then
    if g_r04mode == 2 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr04_go", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "SQ_R4DEMO2")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-555,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-545,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-535,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-525,40,600>/V<0,0,0>")
        if be:FLGisOn(162) ~= 1 then
            for ramNo2 = 49, 66 do
                be:DMsetSD("MODELCTRL", "g_dcap", ramNo2, "SQ_DDMG", 130)
            end
        end
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 240)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "SQ_R0DEMO2")
    elseif g_r04mode == 3 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr04_back", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "SQ_R2DEMO3")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-315,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-305,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-295,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-285,40,600>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 240)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail01", 3, "SQ_R2DEMO5")
    end
end
be:DMcase(1)
be:DMsetSD("MODELCTRL", "r_drail01", ramNo, "OFFREEZE")
be:DMswtEnd()
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
be:DMrun()
