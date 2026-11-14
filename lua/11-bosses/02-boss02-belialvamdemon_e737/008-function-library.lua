_ERRORMESSAGE = function(text)
    be:MsgBox(text, 0)
end
funcPlayerStatusGenerate = function()
    be:sd("MODELCTRL", "i_stpnl00", 0, "GENERATE")
    local local_0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if playerIndex == 0 then
                be:sd("MODELCTRL", "i_stpnl01", 0, "GENERATE", "V<-260,-160,0>")
                be:sd("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>")
                be:sd("MODELCTRL", "i_stpnl03", 0, "GENERATE", "V<-260,-160,0>")
                be:sd("MODELCTRL", "i_stpnl04", 0, "GENERATE", "V<-260,-160,0>")
                be:sd("MODELCTRL", "i_stpnl05", 0, "GENERATE", "V<-260,-160,0>")
            elseif playerIndex == 1 then
                be:sd("MODELCTRL", "i_stpnl01", 1, "GENERATE", "V<-110,-160,0>")
                be:sd("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>")
                be:sd("MODELCTRL", "i_stpnl03", 1, "GENERATE", "V<-110,-160,0>")
                be:sd("MODELCTRL", "i_stpnl04", 1, "GENERATE", "V<-110,-160,0>")
                be:sd("MODELCTRL", "i_stpnl05", 1, "GENERATE", "V<-110,-160,0>")
            elseif playerIndex == 2 then
                be:sd("MODELCTRL", "i_stpnl01", 2, "GENERATE", "V<40,-160,0>")
                be:sd("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>")
                be:sd("MODELCTRL", "i_stpnl03", 2, "GENERATE", "V<40,-160,0>")
                be:sd("MODELCTRL", "i_stpnl04", 2, "GENERATE", "V<40,-160,0>")
                be:sd("MODELCTRL", "i_stpnl05", 2, "GENERATE", "V<40,-160,0>")
            elseif playerIndex == 3 then
                be:sd("MODELCTRL", "i_stpnl01", 3, "GENERATE", "V<190,-160,0>")
                be:sd("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>")
                be:sd("MODELCTRL", "i_stpnl03", 3, "GENERATE", "V<190,-160,0>")
                be:sd("MODELCTRL", "i_stpnl04", 3, "GENERATE", "V<190,-160,0>")
                be:sd("MODELCTRL", "i_stpnl05", 3, "GENERATE", "V<190,-160,0>")
            end
        end
    end
end
funcPlayerStatusSet = function()
    if not g_delayTime then
        g_delayTime = 60
    end
    local local_0
    be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN", g_delayTime + -41)
    be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", playerIndex, "SQ_OPEN")
            be:DMsetSD("MODELCTRL", "i_stpnl02", playerIndex, be:SYSgetPlayerName(playerIndex))
            be:DMsetSD("MODELCTRL", "i_stpnl03", playerIndex, "SQ_OPENWN")
            be:DMsetSD("MODELCTRL", "i_stpnl04", playerIndex, "SQ_OPENWN")
            be:DMsetSD("MODELCTRL", "i_stpnl05", playerIndex, "SQ_WAIT")
        end
    end
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
    be:DMrun()
end
funcPlayerSet = function()
    if be:SYSgetPlayerNinzu() == 0 then
        be:sd("PLAYER", "p_agumon", 0, "GENERATE")
    else
        local local_0
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "GENERATE")
                be:sd("PLAYER2", NULL, playerIndex, "GENESTAGE")
            end
        end
    end
end
funcStageChange = function(arg_0, arg_1, text, arg_3)
    local playerNo = be:MATgetPlayerNo()
    local hp = be:SYSctlPlayer("HP", "GETHP", playerNo, 0)
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if hp ~= 0 then
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
        if text then
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "GENERATE", "SQ_STOPEN", 10)
            be:DMsetSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GENERATE", "V<0,-16,0>/V<0,0,0>", 10)
            be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "STCHGFONT00/font00/CENTER")
            if playerNo == 0 then
                be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.47,0.47>")
            elseif playerNo == 1 then
                be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.47,0.9>")
            elseif playerNo == 2 then
                be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.9,0.47>")
            elseif playerNo == 3 then
                be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.9,0.47>")
            end
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text, 10)
            be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/SET", 30)
        else
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "GENERATE", "SQ_OPEN", 10)
            be:DMsetSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GENERATE", 10)
        end
        be:DMchkSD("MODELCTRL", "i_zzstchgwb", playerNo, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISEND", "!=0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISSELECTNOW", "==1")
        if text then
            be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/CLR")
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "SQ_CLOSE")
        else
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "SQ_CLOSE")
        end
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISEND", "==0")
        be:DMswtSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GETSELECT")
        be:DMcase(0)
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "!=0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
        local local_6
        local local_7
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                local hp2 = be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                if hp2 == 0 then
                    be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISRUN", "!=0")
                end
            end
        end
        if g_StChangeKind == "trans" then
            local local_8
            local offset = 0
            be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
            for playerIndex = 0, 3 do
                if be:SYSisJoinPlayer(playerIndex) == 1 then
                    be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                    offset = offset + 20
                end
            end
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
        else
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01")
        end
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<" .. arg_1 .. ">", 10)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", arg_0, 10)
        be:DMcase(1)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
        be:DMcase(-1)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
        be:DMswtEnd()
        be:DMrun()
    else
        be:sd("PLAYER", nil, -1, "ONCTRL")
        be:sd("ENEMY", nil, -1, "ONCTRL")
    end
end
funcStageIn = function(arg_0)
    g_delayTime = 0
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if arg_0 == "trans" then
        local local_1
        local offset = 30
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_ENTR", offset)
                offset = offset + 20
            end
        end
        g_delayTime = offset + 70
    else
        g_delayTime = 70
    end
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL", g_delayTime)
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL", g_delayTime)
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", g_delayTime)
    be:DMsetSD("MATCTRL", nil, -1, "RESTART", g_delayTime)
    be:DMrun()
end
funcOpenMessage = function(arg_0, arg_1, arg_2)
    g_talk = arg_0
    if arg_0 == "talk" then
        if be:MDLisLive("i_bgclear", 0) == 0 then
            be:DMsetSD("MODELCTRL", "i_bgclear", 0, "GENERATE", "SQ_OPEN")
        elseif be:MDLisLive("i_bgclear", 0) == 1 then
            be:DMsetSD("MODELCTRL", "i_bgclear", 0, "SQ_OPEN")
        end
        be:DMsetSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "GENERATE", "SQ_OPENL")
        be:DMsetSD("MODELCTRL", arg_1 .. "ic", 0, "GENERATE", "SQ_OPENL")
        be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "TALKFONT03/font00/V<0.9,0.9,0.47>")
        if arg_2 == "fWt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC001)
        elseif arg_2 == "Xe[^XEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC002)
        elseif arg_2 == "goloX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC003)
        elseif arg_2 == "A[}E{[hEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC004)
        elseif arg_2 == "AreBE`bvEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC005)
        elseif arg_2 == "«Ùñp[^EX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC006)
        elseif arg_2 == "wf[^eCRE¿X^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC007)
        elseif arg_2 == "»¤ÑX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC008)
        elseif arg_2 == "AreB»¤ÑX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC009)
        elseif arg_2 == "loUEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC010)
        elseif arg_2 == "loUp[^EX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC011)
        elseif arg_2 == "Z[u[hEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC013)
        elseif arg_2 == "Q[gEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC014)
        elseif arg_2 == "tH_EX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC015)
        elseif arg_2 == "EF|EjbgEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC016)
        elseif arg_2 == "ACREX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC017)
        elseif arg_2 == "xgoloX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC018)
        elseif arg_2 == "fW{EX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC019)
        elseif arg_2 == "µñ©UEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC020)
        elseif arg_2 == "ogVXeEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC021)
        elseif arg_2 == "XLVXeEX^bt" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC022)
        elseif arg_2 == "It@j" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC023)
        elseif arg_2 == "ZtB" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC024)
        elseif arg_2 == "I" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC025)
        elseif arg_2 == "^Ge" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC026)
        elseif arg_2 == "vX}" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC027)
        elseif arg_2 == "AO" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC028)
        elseif arg_2 == "uC" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC029)
        elseif arg_2 == "M" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC030)
        elseif arg_2 == "h" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC031)
        elseif arg_2 == "[K" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC032)
        elseif arg_2 == "BLEH[OC" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC033)
        elseif arg_2 == "ÎñØ¢QR" then
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswkNPC034)
        end
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISSEQNAME", "SQ_OPENL", "==0")
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISSEQNAME", "SQ_OPENL", "!=0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT03/font00/SET")
    else
        be:DMsetSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "GENERATE", "SQ_OPEN")
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
        be:DMchkSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    end
end
funcOneMessage = function(text)
    local local_1 = 0
    if g_talk == "talk" then
        local_1 = 2
    else
        local_1 = 1
    end
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_1 .. "/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_" .. g_talk .. "ky", g_messPlayerNo, "GENERATE")
    be:DMchkSD("SELECTCTRL", "i_" .. g_talk .. "ky", g_messPlayerNo, "ISEND", "!=0")
    be:DMchkSD("SELECTCTRL", "i_" .. g_talk .. "ky", g_messPlayerNo, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_1 .. "/font00/CLR")
end
funcChoiceMessage = function(...)
    local local_1
    local local_2 = 0
    local local_3 = "0,0,0"
    if g_talk == "talk" then
        local_2 = 2
        local_3 = "80,-2,0"
    else
        local_2 = 1
        local_3 = "0,-2,0"
    end
    for i = 1, arg.n do
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", arg[i])
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_2 .. "/font0" .. i .. "/SET", 12)
    end
    be:DMsetSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GENERATE", "NOCANCEL/I<" .. arg.n .. ">/V<" .. local_3 .. ">", 12)
    be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "!=0")
    be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "==0")
    for i = 1, arg.n do
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_2 .. "/font0" .. i .. "/CLR")
    end
end
funcCloseMessage = function(arg_0, arg_1, arg_2, arg_3, arg_4)
    if g_talk == "talk" then
        be:DMsetSD("MODELCTRL", "i_bgclear", 0, "SQ_ERAS", 10)
        be:DMsetSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "SQ_CLOSEL")
        be:DMsetSD("MODELCTRL", arg_1 .. "ic", 0, "SQ_CLOSEL")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT03/font00/CLR")
    else
        be:DMsetSD("MODELCTRL", "i_" .. g_talk .. "wn", 0, "SQ_CLOSE")
    end
    if arg_1 ~= "demo" and arg_2 ~= "demo" and arg_3 ~= "demo" and arg_4 ~= "demo" then
        if arg_4 == "noturn" then
        end
    end
    be:DMchkSD("MODELCTRL", "i_" .. arg_0 .. "wn", 0, "ISRUN", "!=0")
end
funcOpenDigimonInfoWin = function(text, text2, text3, text4, sendTime)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 10)
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "DMINFOFONT01/font00/CENTER", 0)
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "DMINFOFONT02/font00/CENTER", 0)
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "DMINFOFONT02/font01/CENTER", 0)
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "DMINFOFONT02/font02/CENTER", 0)
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text, 0)
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text2, 0)
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text3, 0)
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", text4, 0)
    be:DMsetSD("MODELCTRL", "i_dminfown", 0, "GENERATE", "SQ_OPEN", sendTime)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT01/font00/SET", sendTime + 10)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font00/SET", sendTime + 20)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font01/SET", sendTime + 30)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font02/SET", sendTime + 40)
    be:DMsetSD("MODELCTRL", "i_dminfown", 0, "SQ_CLOSE", sendTime + 210)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT01/font00/CLR", sendTime + 210)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font00/CLR", sendTime + 210)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font01/CLR", sendTime + 210)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "DMINFOFONT02/font02/CLR", sendTime + 210)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", sendTime + 240)
end
funcSecurityGate = function(gateStage, gatePos, ramNo)
    local count = 0
    local count2 = 0
    local count3 = 0
    local count4 = 0
    local count5 = 0
    local local_8
    g_GateStage = gateStage
    g_GatePos = gatePos
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if be:MDLisLive(be:SYSgetPlayerName(playerIndex), playerIndex) == 1 then
                count5 = count5 + 1
            end
            if be:MATgetPlayerMatStat(playerIndex) == 0 then
                count4 = count4 + 1
            elseif be:MATgetPlayerMatStat(playerIndex) == 1 then
                count3 = count3 + 1
            elseif be:MATgetPlayerMatStat(playerIndex) == 2 then
                count = count + 1
            elseif be:MATgetPlayerMatStat(playerIndex) == 3 then
                count2 = count2 + 1
            end
        end
    end
    if count + count2 == count5 then
        be:sd("MODELCTRL", "g_security", ramNo, "SQ_SWON")
        g_GateOn = 1
    else
        be:sd("MODELCTRL", "g_security", ramNo, "SQ_SWOF")
        g_GateOn = 0
    end
end
funcHealGate = function(arg_0, infoName, ramNo)
    local count = 0
    local count2 = 0
    local count3 = 0
    local count4 = 0
    local local_7
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if be:MATgetPlayerMatStat(playerIndex) == 0 then
                count4 = count4 + 1
            elseif be:MATgetPlayerMatStat(playerIndex) == 1 then
                count3 = count3 + 1
            elseif be:MATgetPlayerMatStat(playerIndex) == 2 then
                count = count + 1
                local hp = be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                local maxHp = be:SYSctlPlayer("HP", "GETMHP", playerIndex, 0)
                local mp = be:SYSctlPlayer("MP", "GETMP", playerIndex, 0)
                local maxMp = be:SYSctlPlayer("MP", "GETMMP", playerIndex, 0)
                if arg_0 == "ALL" then
                    if hp ~= maxHp and mp ~= maxMp then
                        be:sd("PLAYER", nil, playerIndex, "OFCTRL")
                        be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_JUMP", "==1")
                        be:DMsetSD("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<" .. maxHp .. ">/I<1>")
                        be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">")
                        be:DMsetSD("PLAYER", nil, playerIndex, "ONCTRL", 30)
                        be:DMrun()
                    elseif hp ~= maxHp and mp == maxMp then
                        be:sd("PLAYER", nil, playerIndex, "OFCTRL")
                        be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_JUMP", "==1")
                        be:DMsetSD("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<" .. maxHp .. ">/I<1>")
                        be:DMsetSD("PLAYER", nil, playerIndex, "ONCTRL", 30)
                        be:DMrun()
                    elseif hp == maxHp and mp ~= maxMp then
                        be:sd("PLAYER", nil, playerIndex, "OFCTRL")
                        be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_JUMP", "==1")
                        be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">/I<1>")
                        be:DMsetSD("PLAYER", nil, playerIndex, "ONCTRL", 30)
                        be:DMrun()
                    end
                elseif arg_0 == "HP" then
                    if hp ~= maxHp then
                        be:sd("PLAYER", nil, playerIndex, "OFCTRL")
                        be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_JUMP", "==1")
                        be:DMsetSD("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<" .. maxHp .. ">/I<1>")
                        be:DMsetSD("PLAYER", nil, playerIndex, "ONCTRL", 30)
                        be:DMrun()
                    else
                    end
                elseif arg_0 == "MP" and mp ~= maxMp then
                    be:sd("PLAYER", nil, playerIndex, "OFCTRL")
                    be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_JUMP", "==1")
                    be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">/I<1>")
                    be:DMsetSD("PLAYER", nil, playerIndex, "ONCTRL", 30)
                    be:DMrun()
                end
            elseif be:MATgetPlayerMatStat(playerIndex) == 3 then
                count2 = count2 + 1
            end
        end
    end
    if count >= 1 and count2 == 0 then
        be:sd("MODELCTRL", infoName, ramNo, "SQ_SWON")
    end
    if count + count2 == 0 then
        be:sd("MODELCTRL", infoName, ramNo, "SQ_SWOF")
    end
end
funcTameWazaHitCheck = function()
    if be:MDLgetBulletKind() == 20000 then
        return 1
    else
        return 0
    end
end
funcTechWazaHitCheck = function()
    local bulletKind = be:MDLgetBulletKind()
    if 40040 <= bulletKind and bulletKind <= 40099 then
        return 1
    else
        return 0
    end
end
funcStartLayerSet = function()
    be:sd("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
end
funcFirstLayerSet = function()
    be:sd("LAYERCTL", nil, -1, "REMOVE", "LOADING")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "ALL/DISPON")
end
