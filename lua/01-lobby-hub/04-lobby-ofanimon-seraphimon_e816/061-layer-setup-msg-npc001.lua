mswkNPC001 = "TALKFONT03/font00/I<258>"
mswkNPC002 = "TALKFONT03/font00/I<259>"
mswkNPC003 = "TALKFONT03/font00/I<260>"
mswkNPC004 = "TALKFONT03/font00/I<261>"
mswkNPC005 = "TALKFONT03/font00/I<262>"
mswkNPC006 = "TALKFONT03/font00/I<263>"
mswkNPC007 = "TALKFONT03/font00/I<264>"
mswkNPC008 = "TALKFONT03/font00/I<265>"
mswkNPC009 = "TALKFONT03/font00/I<266>"
mswkNPC010 = "TALKFONT03/font00/I<267>"
mswkNPC011 = "TALKFONT03/font00/I<268>"
mswkNPC013 = "TALKFONT03/font00/I<269>"
mswkNPC014 = "TALKFONT03/font00/I<270>"
mswkNPC015 = "TALKFONT03/font00/I<271>"
mswkNPC016 = "TALKFONT03/font00/I<272>"
mswkNPC017 = "TALKFONT03/font00/I<273>"
mswkNPC018 = "TALKFONT03/font00/I<274>"
mswkNPC019 = "TALKFONT03/font00/I<275>"
mswkNPC020 = "TALKFONT03/font00/I<276>"
mswkNPC021 = "TALKFONT03/font00/I<277>"
mswkNPC022 = "TALKFONT03/font00/I<278>"
mswkNPC023 = "TALKFONT03/font00/I<279>"
mswkNPC024 = "TALKFONT03/font00/I<280>"
PintmessOpen = function(arg_0, text, text2, text3, text4, text5)
    local local_6 = 0
    local local_7 = 0
    local local_8 = 0
    local local_9 = 0
    local local_10
    if not g_pointname then
        g_pointname = 0
    end
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if be:MATgetPlayerMatStat(playerIndex) == 2 then
                if g_joincount == 1 then
                    playerIndex = 4
                end
                if be:MDLisLive("i_pointcur", playerIndex) == 0 then
                    be:sd("MODELCTRL", "i_pointcur", playerIndex, "GENERATE", arg_0 .. "/SQ_OPEN" .. playerIndex)
                elseif be:MDLisLive("i_pointcur", playerIndex) == 1 then
                    be:sd("MODELCTRL", "i_pointcur", playerIndex, "SQ_OPEN" .. playerIndex)
                end
                be:sd("MODELCTRL", "i_stpnl06", playerIndex, "SQ_OPEN")
                if playerIndex == 0 then
                    be:sd("TEXTCTL", nil, -1, "COLOR", "POINTFONT00/font00/V<0.9,0.747,0.747>")
                    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
                elseif playerIndex == 1 then
                    be:sd("TEXTCTL", nil, -1, "COLOR", "POINTFONT00/font01/V<0.747,0.747,0.9>")
                    be:sd("TEXTCTL", nil, -1, "TEXTSET", text2)
                elseif playerIndex == 2 then
                    be:sd("TEXTCTL", nil, -1, "COLOR", "POINTFONT00/font02/V<0.9,0.9,0.747>")
                    be:sd("TEXTCTL", nil, -1, "TEXTSET", text3)
                elseif playerIndex == 3 then
                    be:sd("TEXTCTL", nil, -1, "COLOR", "POINTFONT00/font03/V<0.747,0.9,0.747>")
                    be:sd("TEXTCTL", nil, -1, "TEXTSET", text4)
                elseif playerIndex == 4 then
                    be:sd("TEXTCTL", nil, -1, "ALIGN", "POINTFONT00/font04/CENTER")
                    be:sd("TEXTCTL", nil, -1, "COLOR", "POINTFONT00/font04/V<0.419,0.725,0.780>")
                    be:sd("TEXTCTL", nil, -1, "TEXTSET", text5)
                end
                be:sd("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font0" .. playerIndex .. "/SET")
            elseif be:MATgetPlayerMatStat(playerIndex) == 1 then
                if g_joincount == 1 then
                    playerIndex = 4
                end
                if be:MDLisLive("i_pointcur", playerIndex) == 1 then
                    be:sd("MODELCTRL", "i_pointcur", playerIndex, "SQ_CLOSE")
                elseif be:MDLisLive("i_pointcur", playerIndex) == 0 then
                    be:sd("MODELCTRL", "i_pointcur", playerIndex, "SQ_ERAS")
                end
                be:sd("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font0" .. playerIndex .. "/CLR")
                be:sd("MODELCTRL", "i_stpnl06", playerIndex, "SQ_CLOSE")
            end
        end
    end
end
if be:FLGisOn(502) == 0 then
    if be:DMgetCount() == 0 then
        g_messPlayerNo = 0
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:FLGset(502, 1)
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WAIT02")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "MOVETRANS", "V<-50,10,80>/V<0,-90,0>")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0201")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WALK02", 1)
        local local_0
        local offset = 300
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_ENTR", offset)
                offset = offset + 20
            end
        end
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_WALK02", "==0")
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_WALK02", "!=0")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WAIT", 20)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WALK04", 30)
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_WALK04", "==0")
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_WALK04", "!=0")
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk67066 = "TALKFONT02/font00/I<281>"
        funcOneMessage(mswk67066)
        mswk67067 = "TALKFONT02/font00/I<282>"
        funcOneMessage(mswk67067)
        mswk67068 = "TALKFONT02/font00/I<283>"
        funcOneMessage(mswk67068)
        mswk67069 = "TALKFONT02/font00/I<284>"
        funcOneMessage(mswk67069)
        funcCloseMessage("talk", "n_digilfm", "fWt", 0, "demo")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk67070 = "TALKFONT02/font00/I<285>"
        funcOneMessage(mswk67070)
        mswk67071 = "TALKFONT02/font00/I<286>"
        funcOneMessage(mswk67071)
        mswk67072 = "TALKFONT02/font00/I<287>"
        funcOneMessage(mswk67072)
        funcCloseMessage("talk", "n_digilfm", "fWt", 0, "demo")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk67073 = "TALKFONT02/font00/I<288>"
        funcOneMessage(mswk67073)
        mswk67074 = "TALKFONT02/font00/I<289>"
        funcOneMessage(mswk67074)
        mswk67075 = "TALKFONT02/font00/I<290>"
        funcOneMessage(mswk67075)
        mswk67076 = "TALKFONT02/font00/I<291>"
        funcOneMessage(mswk67076)
        funcCloseMessage("talk", "n_digilfm", "fWt", 0, "demo")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_SHOK")
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_SHOK", "==0")
        be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISSEQNAME", "SQ_SHOK", "!=0")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk67077 = "TALKFONT02/font00/I<292>"
        funcOneMessage(mswk67077)
        mswk67078 = "TALKFONT02/font00/I<293>"
        funcOneMessage(mswk67078)
        mswk67079 = "TALKFONT02/font00/I<294>"
        funcOneMessage(mswk67079)
        funcCloseMessage("talk", "n_digilfm", "fWt", 0, "demo")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "ONCTRL")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WALKON")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 120)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 120)
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 120)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 120)
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 120)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 120)
        be:DMrun()
    end
elseif be:FLGisOn(2) == 1 and be:FLGisOn(20) == 1 and be:FLGisOn(322) == 0 then
    if be:DMgetCount() == 0 then
        g_messPlayerNo = 0
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "SQ_WAIT")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<205,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<185,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<195,60,-90>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<195,60,-110>/V<0,90,0>")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK", 120)
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30201 = "TALKFONT02/font00/I<295>"
        funcOneMessage(mswk30201)
        mswk30202 = "TALKFONT02/font00/I<296>"
        funcOneMessage(mswk30202)
        mswk30203 = "TALKFONT02/font00/I<297>"
        funcOneMessage(mswk30203)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_LEOMN/F<1.0>/F<0.6>/F<120>")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "mlBEEP01", 30)
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 120)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30204 = "TALKFONT02/font00/I<298>"
        funcOneMessage(mswk30204)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 120)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30205 = "TALKFONT02/font00/I<299>"
        funcOneMessage(mswk30205)
        mswk30206 = "TALKFONT02/font00/I<300>"
        funcOneMessage(mswk30206)
        mswk30207 = "TALKFONT02/font00/I<301>"
        funcOneMessage(mswk30207)
        mswk30208 = "TALKFONT02/font00/I<302>"
        funcOneMessage(mswk30208)
        mswk30209 = "TALKFONT02/font00/I<303>"
        funcOneMessage(mswk30209)
        mswk30210 = "TALKFONT02/font00/I<304>"
        funcOneMessage(mswk30210)
        mswk30211 = "TALKFONT02/font00/I<305>"
        funcOneMessage(mswk30211)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30212 = "TALKFONT02/font00/I<306>"
        funcOneMessage(mswk30212)
        mswk30213 = "TALKFONT02/font00/I<307>"
        funcOneMessage(mswk30213)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_LEOMN/F<0.6>/F<0.0>/F<90>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_LEOMN", 91)
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 90)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        funcOpenMessage("mess")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ITEM_GET", 30)
        mswk30214 = "TALKFONT01/font00/I<308>"
        funcOneMessage(mswk30214)
        funcCloseMessage("mess", "demo")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30215 = "TALKFONT02/font00/I<309>"
        funcOneMessage(mswk30215)
        mswk30216 = "TALKFONT02/font00/I<310>"
        funcOneMessage(mswk30216)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 90)
        be:FLGset(322, 1)
        be:SYSctlFlagFolder("SET", 2)
        be:DMrun()
        be:sd("MODELCTRL", "n_digilfm", 0, "SQ_WALKON", 30)
    end
elseif be:FLGisOn(3) == 1 and be:FLGisOn(324) == 1 and be:FLGisOn(325) == 0 then
    if be:DMgetCount() == 0 then
        g_messPlayerNo = 0
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "SQ_WAIT")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "seratalk")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<100,60,-205>/V<0,-180,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<100,60,-185>/V<0,-180,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<110,60,-195>/V<0,-180,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<90,60,-195>/V<0,-180,0>")
        be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 300)
        be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk30501 = "TALKFONT02/font00/I<311>"
        funcOneMessage(mswk30501)
        funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "alarmoff")
        be:DMsetSD("MODELCTRL", "g_indicatorz05", 0, "SQ_SWOF", 150)
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "AM_OFNI2/F<1.0>/F<0.0>/F<120>", 150)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 271)
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_SERAF/F<1.0>/F<0.0>/F<120>", 150)
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_SERAF", 271)
        be:DMchkSD("MODELCTRL", "g_indicatorz05", 0, "ISSEQNAME", "SQ_SWOF", "==0")
        be:DMchkSD("MODELCTRL", "g_indicatorz05", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
        funcOpenMessage("mess")
        mswk30502 = "TALKFONT01/font00/I<312>"
        funcOneMessage(mswk30502)
        funcCloseMessage("mess", "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "seratalk2", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "DM_SERAF", 300)
        be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 300)
        be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk30503 = "TALKFONT02/font00/I<313>"
        funcOneMessage(mswk30503)
        mswk30504 = "TALKFONT02/font00/I<314>"
        funcOneMessage(mswk30504)
        mswk30505 = "TALKFONT02/font00/I<315>"
        funcOneMessage(mswk30505)
        mswk30506 = "TALKFONT02/font00/I<316>"
        funcOneMessage(mswk30506)
        funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
        be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 90)
        be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk30507 = "TALKFONT02/font00/I<317>"
        funcOneMessage(mswk30507)
        mswk30508 = "TALKFONT02/font00/I<318>"
        funcOneMessage(mswk30508)
        mswk30509 = "TALKFONT02/font00/I<319>"
        funcOneMessage(mswk30509)
        mswk30510 = "TALKFONT02/font00/I<320>"
        funcOneMessage(mswk30510)
        funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 130)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 130)
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 130)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 130)
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 130)
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_SERAF/F<1.0>/F<0.0>/F<120>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_SERAF", 121)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 130)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 130)
        be:FLGset(336, 0)
        be:FLGset(325, 1)
        be:FLGset(3, 0)
        be:FLGset(4, 1)
        be:DMrun()
        be:sd("MODELCTRL", "n_digilfm", 0, "SQ_WALKON", 30)
    end
else
    if be:PLAYERgetPos() == 0 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 1 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 2 then
        funcStageIn("trans")
    end
    be:sd("MODELCTRL", "n_digilfm", 0, "SQ_WALKON", 30)
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
