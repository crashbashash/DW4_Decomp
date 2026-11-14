local showText = function(arg_0, arg_1, text, arg_3)
    local playerNo
    playerNo = be:MATgetPlayerNo()
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if text then
        be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "GENERATE", "SQ_STOPEN", 10)
        be:DMsetSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GENERATE", "V<0,-16,0>/V<0,0,0>", 10)
        be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "STCHGFONT00/font00/CENTER")
        if playerNo == 0 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<1.0,0.57,0.57>")
        elseif playerNo == 1 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.57,0.57,1.0>")
        elseif playerNo == 2 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<1.0,1.0,0.57>")
        elseif playerNo == 3 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.57,1.0,0.57>")
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
    local local_5
    local offset = 40
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
            offset = offset + 20
        end
    end
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
    be:DMsetLua("gateclear.lua")
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
end
local gateStageName = be:SYSgetGateStageName()
local gateStageNo = be:SYSgetGateStageNo()
if be:FLGisOn(3) ~= 1 and gateStageName ~= "GateOff" and be:MATisAllPlayer() == 1 and be:FLGisOn(409) == 0 then
    if gateStageName == "dng101b2" then
        mswk70029 = "STCHGFONT00/font00/I<60>"
        showText(gateStageName, gateStageNo, mswk70029, 1)
    else
        if gateStageName ~= "dng102b2" then
            if gateStageName == "dng102b3" then
            end
        end
        mswk70030 = "STCHGFONT00/font00/I<61>"
        showText(gateStageName, gateStageNo, mswk70030, 1)
    end
end
