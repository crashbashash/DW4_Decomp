mswk61002 = "TALKFONT01/font00/I<12>"
mswk61003 = "TALKFONT02/font00/I<13>"
mswk61004 = "TALKFONT02/font00/I<14>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<20,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<220,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<80,10,200>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<160,10,200>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<220,10,140>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<20,10,60>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 6, "GENERATE", "V<220,10,20>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 7, "GENERATE", "V<-80,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 8, "GENERATE", "V<-60,10,-460>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 9, "GENERATE", "V<-60,10,-660>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-5,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<45,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,10,-750>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<120,10,185>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-235,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-205,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<95,10,-285>/V<0,90,0>")
    for local_1 = 1, 8 do
        if be:FLGisOn(local_1 + 115) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", local_1))
        end
    end
    if be:FLGisOn(124) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    end
    if be:FLGisOn(131) ~= 1 then
        if be:FLGisOn(132) == 1 then
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
            be:FLGset(131, 1)
            be:FLGset(132, 1)
        end
    end
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
    be:FLGset(131, 1)
    be:FLGset(132, 1)
    if be:FLGisOn(133) == 1 then
        be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(133) == 1 and be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
        be:FLGset(130, 1)
    else
        be:FLGset(130, 0)
    end
    if be:FLGisOn(135) == 1 then
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(110) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(112) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(113) == 1 then
        be:sd("MODELCTRL", "g_d1door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_d1door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_d1door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d1door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
elseif be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<20,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<220,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<80,10,200>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<160,10,200>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<220,10,140>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<20,10,60>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 6, "GENERATE", "V<220,10,20>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 7, "GENERATE", "V<-80,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 8, "GENERATE", "V<-60,10,-460>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 9, "GENERATE", "V<-60,10,-660>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-5,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<45,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-5,10,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<45,10,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,10,-750>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<120,10,185>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-235,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-205,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<95,10,-285>/V<0,90,0>")
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-180,10,-400>/V<0,-45,0>")
    for local_1 = 1, 8 do
        if be:FLGisOn(local_1 + 115) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_1))
        end
    end
    for local_1 = 0, 3 do
        if be:FLGisOn(124 + local_1) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", local_1, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", local_1, "SQ_POWERON")
        end
    end
    if be:FLGisOn(131) ~= 1 then
        if be:FLGisOn(132) == 1 then
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
            be:FLGset(131, 1)
            be:FLGset(132, 1)
        end
    end
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
    be:FLGset(131, 1)
    be:FLGset(132, 1)
    if be:FLGisOn(133) == 1 then
        be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(133) == 1 and be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
        be:FLGset(130, 1)
    else
        be:FLGset(130, 0)
    end
    if be:FLGisOn(135) == 1 then
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(110) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(112) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(113) == 1 then
        be:sd("MODELCTRL", "g_d1door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_d1door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_d1door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d1door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
elseif be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<20,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<220,10,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<80,10,200>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<160,10,200>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<220,10,140>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<20,10,60>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d1door", 6, "GENERATE", "V<220,10,20>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 7, "GENERATE", "V<-80,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d1door", 8, "GENERATE", "V<-60,10,-460>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d1door", 9, "GENERATE", "V<-60,10,-660>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-5,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<45,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-5,10,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<45,10,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<-5,10,200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 5, "GENERATE", "V<45,10,200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-60,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,10,-750>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<120,10,185>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-235,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-205,10,-415>/V<0,180,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-240,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-220,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-200,10,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-240,10,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-220,10,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<-200,10,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<95,10,-285>/V<0,90,0>")
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-180,10,-400>/V<0,0,0>")
    for local_1 = 1, 8 do
        if be:FLGisOn(local_1 + 115) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", local_1))
        end
    end
    for local_1 = 0, 5 do
        if be:FLGisOn(124 + local_1) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", local_1, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", local_1, "SQ_POWERON")
        end
    end
    if be:FLGisOn(131) ~= 1 then
        if be:FLGisOn(132) == 1 then
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
            be:FLGset(131, 1)
            be:FLGset(132, 1)
        end
    end
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
    be:FLGset(131, 1)
    be:FLGset(132, 1)
    if be:FLGisOn(133) == 1 then
        be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(133) == 1 and be:FLGisOn(134) == 1 then
        be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
        be:FLGset(130, 1)
    else
        be:FLGset(130, 0)
    end
    if be:FLGisOn(135) == 1 then
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(110) == 1 then
        be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(112) == 1 then
        be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(113) == 1 then
        be:sd("MODELCTRL", "g_d1door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_d1door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_d1door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d1door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
else
    be:MsgBox("G[FïÕxªzèOÅ·B")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
