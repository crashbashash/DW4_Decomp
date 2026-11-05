if be:MATisAllPlayer() == 1 and g_IFLG00 == 10 and be:DMgetCount() == 0 then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "g_soukouz02", 0, "SQ_BRAKE")
    be:DMsetSD("MODELCTRL", "g_hundredz06", 0, "GENERATE", "V<2100,210,-750>/V<0,-180,0>/SQ_FALL", 120)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "240860/F<6.0>/F<3.0>/F<16.0>", 140)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "240860/F<4.8>/F<3.0>/F<16.0>", 160)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "240860/F<3.2>/F<3.0>/F<16.0>", 180)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "240860/F<2.0>/F<3.0>/F<16.0>", 200)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "240860/F<0.8>/F<3.0>/F<16.0>", 220)
    be:DMsetSD("MODELCTRL", "g_soukouz02", 0, "SQ_STOP", 280)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT60", 360)
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 then
            be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. local_1 .. ">/I<-99999>", 150)
        end
    end
    be:DMsetSD("PLAYER", nil, -1, "SQ_HIDE", 140)
    be:DMsetSD("PLAYER", nil, -1, "SQ_ERAS", 410)
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<5>", 420)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0201", 420)
    be:DMrun()
end
