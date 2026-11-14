local showText = function(...)
    local local_1
    local local_2 = 2
    local local_3 = "80,-2,0"
    for i = 1, arg.n do
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", arg[i])
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_2 .. "/font0" .. i .. "/SET", 12)
    end
    be:DMsetSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GENERATE", "I<" .. arg.n .. ">/V<" .. local_3 .. ">", 12)
    be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "!=0")
    be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "==0")
    for i = 1, arg.n do
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT0" .. local_2 .. "/font0" .. i .. "/CLR")
    end
end
funcOpenMessage("talk", "n_digilfm", "fWt")
mswk80032 = "TALKFONT02/font00/I<55>"
funcOneMessage(mswk80032)
mswk80049 = "TALKFONT02/font01/I<0>"
mswk80033 = "TALKFONT02/font02/I<56>"
mswk80047 = "TALKFONT02/font03/I<57>"
mswk80034 = "TALKFONT02/font04/I<58>"
mswk80037 = "TALKFONT02/font00/I<59>"
funcChoiceMessage(mswk80049, mswk80033, mswk80047, mswk80034)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001004.lua")
be:DMcase(1)
be:DMsetLua("lv16.lua")
be:DMcase(2)
be:DMsetLua("lv36.lua")
be:DMcase(3)
be:DMsetLua("lv46.lua")
be:DMswtEnd()
be:DMrun()
