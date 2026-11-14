local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<520,10,-320>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<320,10,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<260,10,-260>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<420,10,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<520,10,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<80,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<-120,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<-120,10,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<-280,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-60,10,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<-340,10,-340>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<-480,10,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<-480,10,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 13, "GENERATE", "V<-480,10,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 14, "GENERATE", "V<-340,10,60>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 15, "GENERATE", "V<-380,10,420>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 16, "GENERATE", "V<-220,10,460>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 17, "GENERATE", "V<-180,10,260>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 18, "GENERATE", "V<20,10,260>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<80,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-120,10,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<520,10,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<520,10,110>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<520,10,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-140,10,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-100,10,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<-480,10,-540>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<220,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<260,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<300,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<-100,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 10, "GENERATE", "V<-80,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 11, "GENERATE", "V<-80,10,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 12, "GENERATE", "V<-60,10,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-240,10,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-240,10,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<110,10,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-120,10,-260>/V<0,0,0>")
if be:FLGisOn(185) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-520,0,-540>/V<0,0,0>")
end
if be:FLGisOn(187) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-360,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-320,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-280,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-240,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-160,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-120,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-360,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-320,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-280,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-240,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-200,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-160,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-360,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-320,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-280,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-240,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-160,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-160,0,-420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-200,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-160,0,-380>/V<0,0,0>")
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<440,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<480,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<520,0,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<440,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<480,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<520,0,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<440,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<480,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<520,0,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<520,0,-420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<520,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<520,0,-340>/V<0,0,0>")
end
if be:FLGisOn(186) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<160,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<200,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<240,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<280,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<320,0,20>/V<0,0,0>")
end
if be:FLGisOn(141) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<520,0,60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<520,0,100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<520,0,140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<520,0,180>/V<0,0,0>")
end
if be:FLGisOn(155) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<-200,0,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<-160,0,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<-120,0,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<-80,0,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<-80,0,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 47, "GENERATE", "V<-40,0,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 48, "GENERATE", "V<0,0,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 49, "GENERATE", "V<40,0,420>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<80,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<125,10,-375>/V<0,0,0>")
for i = 1, 26 do
    if be:FLGisOn(i + 156) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
if be:FLGisOn(185) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<-495,10,-540>/V<0,90,0>")
    be:sd("MODELCTRL", "g_d4bkwall", 0, "SQ_CUTRIGHT")
end
if be:FLGisOn(186) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 1, "GENERATE", "V<135,10,20>/V<0,-90,0>")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 7, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 11, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 13, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 14, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 15, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 16, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 17, "SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 18, "SQ_CLEAR")
if be:FLGisOn(183) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(184) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(136) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(137) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(141) == 1 then
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(145) == 1 then
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(146) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(147) == 1 then
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(148) == 1 then
    be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(150) == 1 then
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(151) == 1 then
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
end
if be:FLGisOn(153) == 1 then
    be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
end
if be:FLGisOn(155) == 1 then
    be:sd("MODELCTRL", "g_d4door", 16, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
end
if be:FLGisOn(156) == 1 then
    be:sd("MODELCTRL", "g_d4door", 18, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 15, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 17, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map411b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map411b3", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
