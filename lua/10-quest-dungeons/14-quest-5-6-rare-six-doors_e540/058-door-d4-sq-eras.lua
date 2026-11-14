local local_0 = function(arg_0, arg_1)
    if getn(arg_1) < 1 then
        return 0
    end
    local local_2
    for i = 1, getn(arg_1) do
        if arg_0 == arg_1[i] then
            return i
        end
    end
    return 0
end
local local_1
local point = g_mapBlockStartP[g_destMapBlock]
local playerIndex = g_pNo
g_curMapBlock = g_destMapBlock
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE02", 50)
be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 75)
be:DMchkSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_DEMOWALK", "==0")
be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 105)
be:DMchkSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "ISSEQNAME", "SQ_WAIT", "==0")
for playerIndex2 = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex2) == 1 then
        if be:MDLisLive("g_000bcaps", playerIndex2) == 1 then
            be:DMsetSD("MODELCTRL", "g_000bcaps", playerIndex2, "SQ_ERAS")
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex2), playerIndex2, "GENERATE", be:PLAYERgetDataStr(point, playerIndex2, 0))
            be:DMsetSD("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex2 .. ">/I<" .. be:SYSctlPlayer("HP", "GETMHP", playerIndex2, 0) .. ">", 1)
            be:DMchkSD("PLAYER", be:SYSgetPlayerName(playerIndex2), playerIndex2, "ISRUN", "==0")
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex2), playerIndex2, "OFCTRL")
        else
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex2), playerIndex2, "MOVETRANS", be:PLAYERgetDataStr(point, playerIndex2, 0))
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
for playerIndex2 = 0, 10 do
    be:DMsetSD("MODELCTRL", "g_d4door", playerIndex2, "SQ_SILENTOF")
    be:DMsetSD("HITLANDMODEL", format("doorwall%02d", playerIndex2 + 1), 0, "ONHIT")
end
be:DMsetSD("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
local local_4 = 0
if g_curMapBlock == g_luckyMapBlock then
    local_4 = 5
elseif g_mapBlockStartP[g_curMapBlock] == 2 then
    local_4 = 1
end
if local_4 > 0 then
    if be:SYSgetDifficulty() == 0 then
        for i = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-E%02d", i))
        end
    end
    if be:SYSgetDifficulty() == 1 then
        for i = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-H%02d", i))
        end
    end
    if be:SYSgetDifficulty() == 2 then
        for i = local_4, local_4 + 3 do
            be:DMsetSD("GENERATER", nil, -1, "START", format("GBOX-V%02d", i))
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
for i = 1, 15 do
    if be:FLGisOn(104 + i) == 1 then
        be:DMsetSD("GENERATER", nil, -1, "STOPREVERS", format("GENE-%02d", i))
        be:DMsetSD("GENERATER", nil, -1, "RESET", format("GENE-%02d", i), 1)
        be:FLGset(104 + i, 0)
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
