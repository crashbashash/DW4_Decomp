funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-40,40,40>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<-100,65,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<-100,65,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<160,40,560>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<280,40,560>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<340,40,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<340,40,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<205,40,355>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<235,40,355>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<175,40,385>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<205,40,385>/V<0,135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<235,40,385>/V<0,45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<265,40,385>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 6, "GENERATE", "V<175,40,415>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 7, "GENERATE", "V<205,40,415>/V<0,-135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 8, "GENERATE", "V<235,40,415>/V<0,-45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 9, "GENERATE", "V<265,40,415>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 10, "GENERATE", "V<205,40,445>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 11, "GENERATE", "V<235,40,445>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw6", 0, "GENERATE", "V<205,40,385>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw6", 1, "GENERATE", "V<235,40,385>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw6", 2, "GENERATE", "V<205,40,415>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw6", 3, "GENERATE", "V<235,40,415>/V<0,180,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<50,40,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<70,40,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<20,40,-370>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<20,40,-350>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<100,40,-370>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<100,40,-350>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<50,40,-320>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<70,40,-320>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<-120,40,-200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<-120,40,-180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 10, "GENERATE", "V<-120,40,-160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 11, "GENERATE", "V<-80,40,-200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 12, "GENERATE", "V<-80,40,-180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 13, "GENERATE", "V<-80,40,-160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 14, "GENERATE", "V<-60,40,-10>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 15, "GENERATE", "V<220,40,360>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 16, "GENERATE", "V<220,40,380>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 17, "GENERATE", "V<180,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 18, "GENERATE", "V<200,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 19, "GENERATE", "V<220,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 20, "GENERATE", "V<240,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 21, "GENERATE", "V<260,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 22, "GENERATE", "V<220,40,420>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 23, "GENERATE", "V<220,40,440>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-440,40,560>/V<0,90,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-440,40,560>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<-30,40,-230>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<225,40,-5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 2, "GENERATE", "V<175,40,45>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlasergun", 3, "GENERATE", "V<-145,40,-40>/V<0,90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<260,40,-400>/V<0,0,0>")
if be:FLGisOn(283) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<60,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<100,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<20,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<60,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<100,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<140,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<180,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<60,30,-160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<100,30,-160>/V<0,0,0>")
else
    g_dcap = 1
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-100,65,525>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<80,40,-200>/V<0,0,0>")
for local_1 = 1, 12 do
    if be:FLGisOn(local_1 + 270) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(283) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<205,40,-200>/V<0,90,0>")
    be:sd("MODELCTRL", "g_d4bkwall", 0, "SQ_CUTRIGHT")
end
if be:FLGisOn(284) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<-80,40,-40>/V<0,90,0>")
end
if be:FLGisOn(285) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-395,40,560>/V<0,90,0>")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_CLEAR")
if be:FLGisOn(257) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(260) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(264) == 1 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
for local_1 = 0, 3 do
    be:sd("MODELCTRL", "g_dbarrierw6", local_1, "SQ_POWERON")
end
for local_1 = 0, 11 do
    be:sd("MODELCTRL", "g_dbarrierp", local_1, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map412b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map412b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
