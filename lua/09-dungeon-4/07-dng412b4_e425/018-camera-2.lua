be:DMsetSD("MODELCTRL", "r_drail02", local_1, "ONFREEZE")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:sd("PLAYER", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
g_talk = "mess"
g_page = 0
g_messPlayerNo = 0
mswk62012 = "TALKFONT01/font01/I<15>"
mswk62013 = "TALKFONT01/font02/I<16>"
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
funcChoiceMessage(mswk62012, mswk62013)
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMswtSD("SELECTCTRL", "i_messcr", 0, "GETSELECT")
be:DMcase(0)
be:DMsetSD("PLAYER", nil, -1, "SQ_EXIT")
if local_1 == 0 then
    if g_r01mode == 2 then
        if g_r01station == 1 then
            local_2 = 700
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr01_go01", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEMO2")
        elseif g_r01station == 2 then
            local_2 = 580
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr01_go02", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEMO4")
        else
            local_2 = 450
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr01_go03", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEMO6")
        end
        be:DMsetSD("MODELCTRL", "r_drail02", 0, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<865,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<875,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<885,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<895,100,500>/V<0,0,0>")
        if be:FLGisOn(209) ~= 1 then
            for local_3 = 18, 35 do
                be:DMsetSD("MODELCTRL", "g_dcap", local_3, "SQ_DDMG", local_2 + -170)
            end
        end
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", local_2 + -60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEMO8")
    elseif g_r01mode == 3 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr01_back", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEM10")
        be:DMsetSD("MODELCTRL", "r_drail02", 0, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<25,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<35,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<45,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<55,100,500>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 610)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail02", 0, "SQ_R1DEM12")
    else
    end
end
if local_1 == 1 then
    if g_r02mode == 2 then
        if g_r02station == 1 then
            local_2 = 300
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_go01", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEMO2")
        elseif g_r02station == 2 then
            local_2 = 460
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_go02", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEMO4")
        else
            local_2 = 590
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_go03", 60)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEMO6")
        end
        be:DMsetSD("MODELCTRL", "r_drail02", 1, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-935,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-925,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-915,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-905,100,100>/V<0,0,0>")
        if be:FLGisOn(210) ~= 1 then
            for local_3 = 0, 17 do
                be:DMsetSD("MODELCTRL", "g_dcap", local_3, "SQ_DDMG", local_2 + -170)
            end
        end
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", local_2 + -60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEMO8")
    elseif g_r02mode == 3 then
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "tr02_back", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEM10")
        be:DMsetSD("MODELCTRL", "r_drail02", 1, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-695,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-685,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-675,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-665,100,100>/V<0,0,0>")
        be:DMsetSD("PLAYER", nil, -1, "SQ_ENTR", 240)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
        be:DMsetSD("MODELCTRL", "r_drail02", 1, "SQ_R2DEM12")
    end
end
be:DMcase(1)
be:DMsetSD("MODELCTRL", "r_drail02", local_1, "OFFREEZE")
be:DMswtEnd()
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
be:DMrun()
