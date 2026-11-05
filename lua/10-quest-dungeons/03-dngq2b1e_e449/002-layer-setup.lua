mswkNPC028 = "TALKFONT03/font00/I<9>"
mswkNPC029 = "TALKFONT03/font00/I<10>"
mswkNPC031 = "TALKFONT03/font00/I<11>"
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
if g_intro == 1 then
    be:FLGset(385, 1)
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "QS_START")
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "==1")
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 60)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 105)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "QS_START")
    funcOneMessage(mswk61005)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "startctrl")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
    if be:SYSgetDifficulty() == 0 then
        be:COUNTERset(0, 1800)
    elseif be:SYSgetDifficulty() == 1 then
        be:COUNTERset(0, 2400)
    else
        be:COUNTERset(0, 3000)
    end
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:DMsetSD("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:DMsetSD("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:DMsetSD("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN", 10)
    be:COUNTERset(3, 0)
    be:COUNTERset(4, 0)
    be:COUNTERset(5, 0)
    be:COUNTERset(6, 0)
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 then
            be:DMsetSD("NUMBERCTRL", "questnm0", local_3, "SETVALUE", "I<" .. be:COUNTERget(local_3 + 3) .. ">")
            be:DMsetSD("MODELCTRL", "i_questnm0", local_3, "GENERATE", "V<" .. local_2[local_3 + 1] .. ",-160,0>/SQ_OPEN", 10)
            local_1 = local_1 + 1
        end
    end
    if 1 < local_1 then
        g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
        be:DMsetSD("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
        be:DMsetSD("MODELCTRL", "i_questnm1", 0, "GENERATE", "V<-290,182,0>/SQ_OPEN", 10)
    end
    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_THEME", 30)
    be:DMrun()
elseif be:PLAYERgetPos() == 0 then
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "QS_THEME")
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "==1")
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 60)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 105)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "QS_THEME")
    funcOneMessage(mswk61006)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "startctrl")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:DMsetSD("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:DMsetSD("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:DMsetSD("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN", 10)
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 then
            be:DMsetSD("NUMBERCTRL", "questnm0", local_3, "SETVALUE", "I<" .. be:COUNTERget(local_3 + 3) .. ">")
            be:DMsetSD("MODELCTRL", "i_questnm0", local_3, "GENERATE", "V<" .. local_2[local_3 + 1] .. ",-160,0>/SQ_OPEN", 10)
            local_1 = local_1 + 1
        end
    end
    if 1 < local_1 then
        g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
        be:DMsetSD("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
        be:DMsetSD("MODELCTRL", "i_questnm1", 0, "GENERATE", "V<-290,182,0>/SQ_OPEN", 10)
    end
    be:DMrun()
else
    be:sd("SOUND", nil, -1, "PLAY", "QS_THEME")
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 then
            be:sd("NUMBERCTRL", "questnm0", local_3, "SETVALUE", "I<" .. be:COUNTERget(local_3 + 3) .. ">")
            be:sd("MODELCTRL", "i_questnm0", local_3, "GENERATE", "V<" .. local_2[local_3 + 1] .. ",-160,0>/SQ_OPEN", 60)
            local_1 = local_1 + 1
        end
    end
    if 1 < local_1 then
        g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
        be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
        be:sd("MODELCTRL", "i_questnm1", 0, "GENERATE", "V<-290,182,0>/SQ_OPEN", 60)
    end
    be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
    be:sd("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN", 60)
    if be:FLGisOn(144) == 1 then
        be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 61)
    end
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
