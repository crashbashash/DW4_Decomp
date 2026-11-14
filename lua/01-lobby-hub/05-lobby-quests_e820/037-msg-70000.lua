local showText = function(...)
    local local_1
    local ramNo = 0
    local count = 0
    be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    for i = 1, arg.n do
        local local_7 = strfind(arg[i], "STCHGFONT")
        if local_7 == 1 then
            be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "STCHGFONT01/font0" .. i / 3 .. "/CENTER")
            be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", arg[i])
            be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT01/font0" .. i / 3 .. "/SET", 22)
            count = count + 1
        end
    end
    be:DMsetSD("SELECTCTRL", "i_zzstchgcur", ramNo, "GENERATE", "I<" .. arg.n / 3 .. ">", 12)
    be:DMchkSD("SELECTCTRL", "i_zzstchgcur", ramNo, "ISEND", "!=0")
    be:DMchkSD("SELECTCTRL", "i_zzstchgcur", ramNo, "ISSELECTNOW", "==1")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT01/font01/CLR")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT01/font02/CLR")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT01/font03/CLR")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT01/font04/CLR")
    be:DMchkSD("SELECTCTRL", "i_zzstchgcur", ramNo, "ISEND", "==0")
    be:DMswtSD("SELECTCTRL", "i_zzstchgcur", ramNo, "GETSELECT")
    be:DMcase(0)
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    if count >= 1 then
        local local_4 = arg[1]
        local local_5 = arg[2]
        local local_6
        local offset = 40
        be:DMsetLua("gateclear.lua")
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                offset = offset + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<" .. local_5 .. ">", offset + 130)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", local_4, offset + 130)
    end
    be:DMcase(1)
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    if count >= 2 then
        local local_4 = arg[4]
        local local_5 = arg[5]
        local local_6
        local offset = 40
        be:DMsetLua("gateclear.lua")
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                offset = offset + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<" .. local_5 .. ">", offset + 130)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", local_4, offset + 130)
    end
    be:DMcase(2)
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    if count >= 3 then
        local local_4 = arg[7]
        local local_5 = arg[8]
        local local_6
        local offset = 40
        be:DMsetLua("gateclear.lua")
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                offset = offset + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<" .. local_5 .. ">", offset + 130)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", local_4, offset + 130)
    end
    be:DMcase(3)
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    if count == 4 then
        local local_4 = arg[10]
        local local_5 = arg[11]
        local local_6
        local offset = 40
        be:DMsetLua("gateclear.lua")
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                offset = offset + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<" .. local_5 .. ">", offset + 130)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", local_4, offset + 130)
    end
    be:DMcase(-1)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
    be:DMswtEnd()
end
mswk70000 = "STCHGFONT01/font01/I<54>"
mswk70010 = "STCHGFONT01/font02/I<55>"
mswk70016 = "STCHGFONT01/font03/I<56>"
mswk70021 = "STCHGFONT01/font04/I<57>"
mswk70057 = "STCHGFONT01/font01/I<58>"
if be:FLGisOn(2) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        if be:FLGisOn(503) == 0 then
            showText("stag0001", 0, mswk70000)
        else
            showText("stag0101", 0, mswk70000)
        end
        be:DMrun()
    end
elseif be:FLGisOn(4) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        showText("stag0101", 0, mswk70000, "stag0201", 0, mswk70010)
        be:DMrun()
    end
elseif be:FLGisOn(5) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        showText("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016)
        be:DMrun()
    end
elseif be:FLGisOn(6) == 1 and be:FLGisOn(409) == 0 then
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    if be:MATisAllPlayer() == 1 then
        showText("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016, "stag0401", 0, mswk70021)
        be:DMrun()
    end
elseif be:FLGisOn(86) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        showText("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016, "stag0401", 0, mswk70021)
        be:DMrun()
    end
elseif be:FLGisOn(409) == 1 and be:MATisAllPlayer() == 1 then
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    showText("stag0401", 3, mswk70057)
    be:DMrun()
end
