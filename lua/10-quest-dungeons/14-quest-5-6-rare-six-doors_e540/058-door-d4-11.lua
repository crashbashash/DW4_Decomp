g_curMapBlock = g_destMapBlock
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE02", 50)
be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 75)
be:DMchkSD("PLAYER", be:SYSgetPlayerName(local_3), local_3, "ISSEQNAME", "SQ_DEMOWALK", "==0")
be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 105)
be:DMchkSD("PLAYER", be:SYSgetPlayerName(local_3), local_3, "ISSEQNAME", "SQ_WAIT", "==0")
for local_4 = 0, 3 do
    if be:SYSisJoinPlayer(local_4) == 1 then
        if be:MDLisLive("g_000bcaps", local_4) == 1 then
            be:DMsetSD("MODELCTRL", "g_000bcaps", local_4, "SQ_ERAS")
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_4), local_4, "GENERATE", be:PLAYERgetDataStr(local_2, local_4, 0))
            be:DMsetSD("GAMERAM", nil, 0, "ADDHP", "I<" .. local_4 .. ">/I<" .. be:SYSctlPlayer("HP", "GETMHP", local_4, 0) .. ">", 1)
            be:DMchkSD("PLAYER", be:SYSgetPlayerName(local_4), local_4, "ISRUN", "==0")
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_4), local_4, "OFCTRL")
        else
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_4), local_4, "MOVETRANS", be:PLAYERgetDataStr(local_2, local_4, 0))
        end
    end
end
if be:FLGisOn(100) == 1 then
    be:DMsetSD("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<280,40,220>/V<0,-90,0>")
    be:FLGset(100, 0)
end
if be:FLGisOn(101) == 1 then
    be:DMsetSD("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<880,40,220>/V<0,-90,0>")
    be:FLGset(101, 0)
end
if be:FLGisOn(102) == 1 then
    be:DMsetSD("MODELCTRL", "g_dscrap", 2, "GENERATE", "V<1480,40,220>/V<0,-90,0>")
    be:FLGset(102, 0)
end
if be:FLGisOn(103) == 1 then
    be:DMsetSD("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<875,40,100>/V<0,-90,0>")
    be:FLGset(103, 0)
end
if be:FLGisOn(104) == 1 then
    be:DMsetSD("MODELCTRL", "g_dcap", 0, "GENERATE", "V<900,30,100>/V<0,0,0>")
    be:DMsetSD("MODELCTRL", "g_dcap", 1, "GENERATE", "V<940,30,100>/V<0,0,0>")
    be:DMsetSD("MODELCTRL", "g_dcap", 2, "GENERATE", "V<940,30,60>/V<0,0,0>")
    be:DMsetSD("MODELCTRL", "g_dcap", 3, "GENERATE", "V<940,30,20>/V<0,0,0>")
    be:DMsetSD("MODELCTRL", "g_dcap", 4, "GENERATE", "V<940,30,-20>/V<0,0,0>")
    be:FLGset(104, 0)
end
for local_4 = 0, 10 do
    be:DMsetSD("MODELCTRL", "g_d4door", local_4, "SQ_SILENTOF")
    be:DMsetSD("HITLANDMODEL", format("doorwall%02d", local_4 + 1), 0, "ONHIT")
end
be:DMsetSD("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
if g_curMapBlock == g_luckyMapBlock then
    local_4 = 5
elseif g_mapBlockStartP[g_curMapBlock] == 2 then
    local_4 = 1
end
if local_4 > 0 then
    if be:SYSgetDifficulty() == 0 then
        for local_5 = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-E%02d", local_5))
        end
    end
    if be:SYSgetDifficulty() == 1 then
        for local_5 = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_5))
        end
    end
    if be:SYSgetDifficulty() == 2 then
        for local_5 = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-V%02d", local_5))
        end
    end
end
be:DMsetSD("MODELCTRL", "n_dorumon", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "n_agumon", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "n_girumon", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000weapon", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000armor", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000access", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000item", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000bit", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000xdata1", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000xdata2", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000boost1", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_000penx", -1, "SQ_ERAS")
for local_5 = 1, 15 do
    if be:FLGisOn(104 + local_5) == 1 then
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", format("GENE-%02d", local_5))
        be:DMsetSD("GENERATER", nil, -1, "RESET", format("GENE-%02d", local_5), 1)
        be:FLGset(104 + local_5, 0)
    end
end
if local_0(g_curMapBlock, g_dorumon01MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-1147,40,580>/V<0,45,0>", 1)
elseif local_0(g_curMapBlock, g_dorumon02MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-667,40,580>/V<0,45,0>", 1)
end
if local_0(g_curMapBlock, g_agumon01MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_agumon", 0, "GENERATE", "V<440,40,-40>/V<0,-45,0>", 1)
elseif local_0(g_curMapBlock, g_agumon02MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_agumon", 0, "GENERATE", "V<880,40,-40>/V<0,-45,0>", 1)
end
if local_0(g_curMapBlock, g_girumon01MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_girumon", 0, "GENERATE", "V<260,40,-187>/V<0,0,0>", 1)
elseif local_0(g_curMapBlock, g_girumon02MapBlock) > 0 then
    be:DMsetSD("MODELCTRL", "n_girumon", 0, "GENERATE", "V<860,40,-187>/V<0,0,0>", 1)
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 1)
be:DMsetSD("PLAYER", nil, -1, "ONCTRL", 31)
be:DMsetSD("ENEMY", nil, -1, "ONCTRL", 31)
be:DMrun()
