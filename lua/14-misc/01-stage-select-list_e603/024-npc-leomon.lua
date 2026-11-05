funcOpenMessage("talk", "n_leomon", "I")
mswk80000 = "TALKFONT02/font00/I<84>"
funcOneMessage(mswk80000)
mswk80001 = "TALKFONT02/font01/I<85>"
mswk80002 = "TALKFONT02/font02/I<86>"
funcChoiceMessage(mswk80001, mswk80002)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_EXIT", local_1)
        local_1 = local_1 + 20
    end
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", local_1 + 40)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 1)
be:DMcase(1)
funcCloseMessage("talk", "n_leomon", "I")
be:DMswtEnd()
be:DMrun()
