mswk61000 = "TALKFONT01/font00/I<10>"
mswk61001 = "TALKFONT01/font00/I<11>"
local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 901
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
    g_intro = 1
end
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<260,40,-300>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<260,40,-260>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<260,40,-220>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-200,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<40,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<260,40,120>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<260,40,-40>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<260,40,-200>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<220,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<260,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<300,40,-20>/V<0,0,0>")
    for flagNo = 1, 2 do
        if be:FLGisOn(flagNo + 104) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", flagNo))
        end
    end
    if be:SYSgetPlayerNinzu() <= 2 then
        be:FLGset(108, 1)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
    end
    if be:SYSgetPlayerNinzu() == 1 then
        be:FLGset(109, 1)
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_POWERON")
    end
    if be:FLGisOn(107) + be:FLGisOn(108) + be:FLGisOn(109) == 3 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(101) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(103) ~= 1 then
        be:FLGset(102, 0)
    end
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
elseif be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<260,40,-300>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<260,40,-260>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<260,40,-220>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-200,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<40,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<260,40,120>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<260,40,-40>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<260,40,-200>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<220,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<260,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<300,40,-20>/V<0,0,0>")
    for flagNo = 1, 2 do
        if be:FLGisOn(flagNo + 104) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", flagNo))
        end
    end
    if be:SYSgetPlayerNinzu() <= 2 then
        be:FLGset(108, 1)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
    end
    if be:SYSgetPlayerNinzu() == 1 then
        be:FLGset(109, 1)
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_POWERON")
    end
    if be:FLGisOn(107) + be:FLGisOn(108) + be:FLGisOn(109) == 3 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(101) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(103) ~= 1 then
        be:FLGset(102, 0)
    end
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
elseif be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<260,40,-300>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<260,40,-260>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<260,40,-220>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-200,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<40,40,180>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<260,40,120>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<260,40,-40>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<260,40,-200>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<220,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<260,40,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<300,40,-20>/V<0,0,0>")
    for flagNo = 1, 2 do
        if be:FLGisOn(flagNo + 104) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", flagNo))
        end
    end
    if be:SYSgetPlayerNinzu() <= 2 then
        be:FLGset(108, 1)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
    end
    if be:SYSgetPlayerNinzu() == 1 then
        be:FLGset(109, 1)
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_POWERON")
    end
    if be:FLGisOn(107) + be:FLGisOn(108) + be:FLGisOn(109) == 3 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(101) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(103) ~= 1 then
        be:FLGset(102, 0)
    end
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
else
    be:MsgBox("G[FïÕxªzèOÅ·B")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
