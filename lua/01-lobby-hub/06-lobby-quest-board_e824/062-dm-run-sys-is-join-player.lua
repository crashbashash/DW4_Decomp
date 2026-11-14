local local_0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:COUNTERset(playerIndex + 8, be:SYSgetPlayerDigimon(playerIndex))
    end
end
be:DMsetSD("MODELCTRL", "i_talkwn", 0, "SQ_CLOSEL")
be:DMsetSD("MODELCTRL", "n_digilffic", 0, "SQ_CLOSEL")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT03/font00/CLR")
be:DMchkSD("MODELCTRL", "i_talkwn", 0, "ISRUN", "!=0")
be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
be:DMsetSD("MODELCTRL", "n_digilff", g_npcRamNo, "SQ_WAIT")
be:DMsetSD("SUBWND", nil, 0, "GENERATE", "LABO/I<" .. g_messPlayerNo .. ">")
be:DMrun()
