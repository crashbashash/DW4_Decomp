funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
end
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<385,10,-265>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<-235,10,45>/V<0,180,0>")
be:sd("MODELCTRL", "g_dtwbase", 0, "GENERATE", "V<-160,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtwbase", 1, "GENERATE", "V<-80,10,140>/V<0,270,0>")
be:sd("MODELCTRL", "g_dtwbase", 2, "GENERATE", "V<-360,10,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtwbase", 3, "GENERATE", "V<-280,10,-260>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-160,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-80,10,140>/V<0,270,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<-360,10,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<-280,10,-260>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<-20,10,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<20,10,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<-20,10,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<20,10,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<100,35,-300>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<300,35,-300>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<240,10,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<240,10,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 8, "GENERATE", "V<400,10,-220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 9, "GENERATE", "V<240,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 10, "GENERATE", "V<140,35,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 11, "GENERATE", "V<-160,10,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 12, "GENERATE", "V<-120,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 13, "GENERATE", "V<-240,10,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 14, "GENERATE", "V<-240,10,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 15, "GENERATE", "V<-280,35,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 16, "GENERATE", "V<-260,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 17, "GENERATE", "V<-160,35,-360>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 18, "GENERATE", "V<-160,35,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-165,10,135>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-75,10,135>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<-365,10,-265>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<-275,10,-265>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<135,10,335>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<165,10,335>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 2, "GENERATE", "V<-15,10,-25>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 3, "GENERATE", "V<15,10,-25>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 4, "GENERATE", "V<285,10,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 5, "GENERATE", "V<315,10,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 6, "GENERATE", "V<235,10,-155>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlasergun", 7, "GENERATE", "V<365,10,-125>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-160,10,410>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-160,10,410>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 0, "GENERATE", "V<0,10,220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 1, "GENERATE", "V<0,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 2, "GENERATE", "V<240,10,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 3, "GENERATE", "V<-240,10,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-160,10,255>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-85,10,255>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<240,10,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<360,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<240,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<40,10,220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<-240,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 5, "GENERATE", "V<-210,10,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 6, "GENERATE", "V<-40,10,-100>/V<0,0,0>")
if be:FLGisOn(131) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<40,0,380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<80,0,380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<120,0,340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<120,0,380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<120,0,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<160,0,340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<160,0,380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<160,0,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<200,0,340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<200,0,380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<200,0,420>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<0,10,25>/V<0,0,0>")
for local_2 = 1, 10 do
    if be:FLGisOn(local_2 + 109) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_2))
    end
end
if be:FLGisOn(131) ~= 1 then
    be:sd("MODELCTRL", "g_dtbkwall", 0, "GENERATE", "V<15,10,380>/V<0,-90,0>")
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 10, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 11, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 12, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 13, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 14, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 15, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 16, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 17, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 18, "SQ_CLEAR")
if be:FLGisOn(120) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
end
if be:FLGisOn(121) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(120) + be:FLGisOn(121) == 2 then
    be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(122) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(123) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(126) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 13, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 14, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
end
if be:FLGisOn(127) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 17, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
end
if be:FLGisOn(128) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 6, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 6, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(124) + be:FLGisOn(125) == 2 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dtdoor", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
else
    be:FLGset(124, 0)
    be:FLGset(125, 0)
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
end
if be:FLGisOn(129) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(130) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 16, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
end
if be:FLGisOn(102) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(104) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(105) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(107) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 15, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
end
if be:FLGisOn(109) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 18, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map206f1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map206f1", 0, "GENERATE", "SQ_OPEN")
    end
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 and be:MDLisLive("j_mapcur", local_3) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_3, "GENERATE")
        end
    end
end
