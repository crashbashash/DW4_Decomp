mswkNPC001 = "TALKFONT03/font00/I<102>"
mswkNPC025 = "TALKFONT03/font00/I<103>"
mswkNPC027 = "TALKFONT03/font00/I<104>"
mswkNPC028 = "TALKFONT03/font00/I<105>"
mswkNPC029 = "TALKFONT03/font00/I<106>"
mswkNPC030 = "TALKFONT03/font00/I<107>"
mswkNPC031 = "TALKFONT03/font00/I<108>"
if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 3 then
    be:FLGset(364, 0)
    local local_0
    local count = 0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            count = count + 1
        end
    end
    if count == 1 then
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-455,52.5,185>/V<0,88.41,0>")
    end
    be:DMsetSD("MODELCTRL", "g_cydigi", 0, "SQ_SWON02")
    be:DMsetSD("MODELCTRL", "g_cydigi", 0, "SQ_SWOF", 80)
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 4 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 5 then
    funcStageIn("trans")
end
be:sd("MODELCTRL", "n_agumon", 0, "SQ_WALKON", 10)
be:sd("MODELCTRL", "n_agumon", 1, "SQ_WALKON", 22)
be:sd("MODELCTRL", "n_vmon", 0, "SQ_WALKON", 26)
be:sd("MODELCTRL", "n_vmon", 1, "SQ_WALKON", 30)
be:sd("MODELCTRL", "n_vmon", 2, "SQ_WALKON", 38)
be:sd("MODELCTRL", "n_girumon", 0, "SQ_WALKON", 42)
be:sd("MODELCTRL", "n_girumon", 1, "SQ_WALKON", 46)
be:sd("MODELCTRL", "n_dorumon", 0, "SQ_WALKON", 54)
be:sd("MODELCTRL", "n_dorumon", 1, "SQ_WALKON", 58)
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
