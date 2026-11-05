if local_1.category == "flag" then
    local_2 = be:SYSctlFlagFolder("CLR", local_1.number)
    if local_2 == 1 then
        be:DMsetSD("MODELCTRL", "g_mecha", 0, "GENERATE", local_4)
    else
    end
end
if local_1.category == "weapon" then
    local_2 = be:SYSctlDeviceFolder("CLR", 0, "weapon", local_1.number)
    if local_2 == 1 then
        be:DMsetSD("MODELCTRL", "g_qweapon", 0, "GENERATE", local_4)
    else
        local_3 = be:SYSctlDeviceFolder("ISEQUIP", 0, "weapon", local_1.number)
    end
end
if local_1.category == "armor1" then
    local_2 = be:SYSctlDeviceFolder("CLR", 0, "armor1", local_1.number)
    if local_2 == 1 then
        be:DMsetSD("MODELCTRL", "g_qarmor", 0, "GENERATE", local_4)
    else
        local_3 = be:SYSctlDeviceFolder("ISEQUIP", 0, "armor1", local_1.number)
    end
end
if local_1.category == "armor2" then
    local_2 = be:SYSctlDeviceFolder("CLR", 0, "armor2", local_1.number)
    if local_2 == 1 then
        be:DMsetSD("MODELCTRL", "g_qarmor", 0, "GENERATE", local_4)
    else
        local_3 = be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", local_1.number)
    end
end
if local_1.category == "abChip" then
    local_2 = be:SYSctlDeviceFolder("CLR", 0, "abChip", local_1.number)
    if local_2 == 1 then
        be:DMsetSD("MODELCTRL", "g_qaccess", 0, "GENERATE", local_4)
    else
        local_3 = be:SYSctlDeviceFolder("ISEQUIP", 0, "abChip", local_1.number)
    end
end
if local_1.category == "disk" then
    local_2 = be:SYSctlDiskFolder("CLR", 0, local_1.number)
else
    be:MsgBox("LuaàÅÌ¨¦ÌJeSwèÉ~Xª èÜ·B")
end
if local_2 == 0 then
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    if local_3 == 1 then
        funcOneMessage(mswk61095)
    else
        funcOneMessage(mswk61096)
    end
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
    be:DMrun()
    return nil, g_putItemList[g_putItemSelection], nil, 0, "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR"
end
if local_1.result == 0 then
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.1>/F<3.0>/F<120.0>", 60)
    be:DMsetSD("SOUND", nil, -1, "PLAY", "cmQUAKE", 90)
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "cmQUAKE/F<0.0>/F<1.0>/F<150>", 91)
    if local_1.category == "weapon" then
        be:DMsetSD("MODELCTRL", "g_qweapon", 0, "SQ_DDMG", 150)
    else
        if local_1.category ~= "armor1" then
            if local_1.category == "armor2" then
                be:DMsetSD("MODELCTRL", "g_qarmor", 0, "SQ_DDMG", 150)
            elseif local_1.category == "abChip" then
                be:DMsetSD("MODELCTRL", "g_qaccess", 0, "SQ_DDMG", 150)
            end
        end
        be:DMsetSD("MODELCTRL", "g_qarmor", 0, "SQ_DDMG", 150)
    end
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "cmQUAKE/F<1.0>/F<0.0>/F<30>", 180)
    be:DMsetSD("SOUND", nil, -1, "SESTOP", "cmQUAKE", 211)
    be:DMchkSD("SOUND", nil, -1, "ISREADY", "cmQUAKE", "==1")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
    if be:SYSgetDifficulty() == 0 then
    elseif be:SYSgetDifficulty() == 1 then
        if be:FLGisOn(143) ~= 1 then
            for local_5 = 0, 7 do
                be:DMsetSD("MODELCTRL", "g_ddamagefloor", local_5, "SETLABEL", "SQ_WAIT/ON")
            end
            be:DMsetSD("MODELCTRL", "g_darrowshotter", 0, "SQ_POWERON")
            be:DMsetSD("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON")
            be:FLGset(143, 1)
        else
        end
    end
    if be:SYSgetDifficulty() == 2 and be:FLGisOn(143) ~= 1 then
        be:DMsetSD("MODELCTRL", "g_d3door", 10, "SQ_SWOF", 30)
        be:DMsetSD("HITLANDMODEL", "doorwall11", 0, "ONHIT")
        be:DMsetSD("GENERATER", nil, -1, "RESTART", "GENE-14", 45)
        be:FLGset(143, 1)
    end
    be:DMrun()
else
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_THEME/F<1.0>/F<0.0>/F<60>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", 61)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.1>/F<3.0>/F<120.0>", 120)
    be:DMsetSD("SOUND", nil, -1, "PLAY", "cmQUAKE", 150)
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "cmQUAKE/F<0.0>/F<1.0>/F<150>", 151)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.2>/F<3.0>/F<120.0>", 180)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.3>/F<3.0>/F<120.0>", 240)
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.4>/F<3.0>/F<120.0>", 300)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 360)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 360)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN", 360)
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.1>/F<3.0>/F<216000.0>")
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "QS_HURRY")
    funcOneMessage(mswk61017)
    funcOneMessage(mswk61018)
    funcOneMessage(mswk61019)
    funcOneMessage(mswk61020)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "QS_HURRY")
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
    funcOneMessage(mswk61060)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "15/F<0.2>/F<3.0>/F<30.0>")
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "cmQUAKE/F<1.0>/F<0.0>/F<30>")
    be:DMsetSD("SOUND", nil, -1, "SESTOP", "cmQUAKE", 31)
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
    be:COUNTERset(0, 900)
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:DMsetSD("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN")
    if be:SYSgetDifficulty() == 2 then
        be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SWOF")
        be:sd("MODELCTRL", "g_d3door", 11, "SQ_SILENTOF")
        be:sd("HITLANDMODEL", "doorwall12", 0, "ONHIT")
    end
    be:DMrun()
    be:FLGset(121, 1)
    if local_1.result == 2 then
        be:FLGset(562, 1)
    end
    be:FLGset(106, 0)
end
