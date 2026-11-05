be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<0>")
mswkNPC001 = "TALKFONT03/font00/I<36>"
mswkNPC025 = "TALKFONT03/font00/I<37>"
mswkNPC028 = "TALKFONT03/font00/I<38>"
if be:FLGisOn(501) == 0 then
    be:FLGset(508, 1)
    if be:DMgetCount() == 0 then
        g_messPlayerNo = 0
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 10)
        be:sd("MODELCTRL", "n_digilff", 2, "MOVETRANS", "V<60,10,-10>/V<0,117,0>", 5)
        be:sd("MODELCTRL", "n_digilff", 2, "SQ_WAIT02", 5)
        be:sd("MODELCTRL", "n_digilff", 3, "MOVETRANS", "V<63.12,10,-55.8>/V<0,78.8,0>", 5)
        be:sd("MODELCTRL", "n_digilfm", 0, "MOVETRANS", "V<69.11,10,-13.79>/V<0,-90,0>", 5)
        be:sd("MODELCTRL", "n_digilfm", 0, "SQ_WAIT02", 5)
        be:FLGset(501, 1)
        be:sd("PLAYER", nil, -1, "OFCTRL", 5)
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0101")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK", 20)
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_WAIT02", 50)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_TALK", 60)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WAIT02", 110)
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK", 100)
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_WAIT02", 160)
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK", 180)
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_WAIT02", 210)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_TALK", 190)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WAIT02", 220)
        be:DMsetSD("MODELCTRL", "n_digilff", 3, "SQ_WALK")
        for local_2 = 0, 3 do
            if be:SYSisJoinPlayer(local_2) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_ENTR", local_1)
                local_1 = local_1 + 20
            end
        end
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_WALK02")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WALK03", 20)
        be:DMchkSD("MODELCTRL", "n_digilff", 2, "ISSEQNAME", "SQ_WALK02", "==0")
        be:DMchkSD("MODELCTRL", "n_digilff", 2, "ISSEQNAME", "SQ_WALK02", "!=0")
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk67051 = "TALKFONT02/font00/I<39>"
        funcOneMessage(mswk67051)
        mswk67052 = "TALKFONT02/font00/I<40>"
        funcOneMessage(mswk67052)
        mswk67053 = "TALKFONT02/font00/I<41>"
        funcOneMessage(mswk67053)
        funcCloseMessage("talk", "n_digilff", "fWt", 2, "demo")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK")
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk67054 = "TALKFONT02/font00/I<42>"
        funcOneMessage(mswk67054)
        mswk67055 = "TALKFONT02/font00/I<43>"
        funcOneMessage(mswk67055)
        mswk67056 = "TALKFONT02/font00/I<44>"
        funcOneMessage(mswk67056)
        mswk67057 = "TALKFONT02/font00/I<45>"
        funcOneMessage(mswk67057)
        mswk67058 = "TALKFONT02/font00/I<46>"
        funcOneMessage(mswk67058)
        funcCloseMessage("talk", "n_digilff", "fWt", 2, "demo")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK")
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk67059 = "TALKFONT02/font00/I<47>"
        funcOneMessage(mswk67059)
        mswk67060 = "TALKFONT02/font00/I<48>"
        funcOneMessage(mswk67060)
        funcCloseMessage("talk", "n_digilff", "fWt", 2, "demo")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "mlBEEP01")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_DELAY01")
        be:DMchkSD("MODELCTRL", "n_digilff", 2, "ISSEQNAME", "SQ_DELAY01", "==0")
        be:DMchkSD("MODELCTRL", "n_digilff", 2, "ISSEQNAME", "SQ_DELAY01", "!=0")
        funcOpenMessage("mess", "n_digilff", "fWt")
        mswk67061 = "TALKFONT01/font00/I<49>"
        funcOneMessage(mswk67061)
        mswk67062 = "TALKFONT01/font00/I<50>"
        funcOneMessage(mswk67062)
        funcCloseMessage("mess", "n_digilff", "fWt", 2, "demo")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_TALK")
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk67063 = "TALKFONT02/font00/I<51>"
        funcOneMessage(mswk67063)
        mswk67064 = "TALKFONT02/font00/I<52>"
        funcOneMessage(mswk67064)
        mswk67065 = "TALKFONT02/font00/I<53>"
        funcOneMessage(mswk67065)
        funcCloseMessage("talk", "n_digilff", "fWt", 2, "demo")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "ONCTRL")
        be:DMsetSD("MODELCTRL", "n_digilff", 2, "SQ_WALKON")
        be:DMsetSD("MODELCTRL", "n_digilff", 3, "SQ_WAIT")
        be:DMsetSD("MODELCTRL", "n_digilff", 3, "MOVETRANS", "V<240,40,-150>/V<0,0,0>", 10)
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_WAIT")
        be:DMsetSD("MODELCTRL", "n_digilfm", 0, "MOVETRANS", "V<258.187,40,174>/V<0,180,0>", 10)
        be:DMsetSD("MODELCTRL", "n_agumon", 0, "SQ_WALKON", 14)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 120)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 120)
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 120)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 120)
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 120)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 120)
        be:DMrun()
    else
    end
end
if be:PLAYERgetPos() == 0 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 3 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 4 then
    funcStageIn("stay")
end
be:sd("MODELCTRL", "n_digilff", 2, "SQ_WALKON", 25)
be:sd("MODELCTRL", "n_agumon", 0, "SQ_WALKON", 14)
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
