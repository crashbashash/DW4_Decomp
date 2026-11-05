funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_sandfalls", 0, "GENERATE", "V<-340,20,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_sandfalls", 1, "GENERATE", "V<220,20,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_sandfalls", 2, "GENERATE", "V<-60,20,640>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<-60,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 1, "GENERATE", "V<-60,10,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<-60,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealbase", 1, "GENERATE", "V<-60,10,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<300,10,-522>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 0, "GENERATE", "V<265,10,-520>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 1, "GENERATE", "V<335,10,-520>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-197,10,-480>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<77,10,-480>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-60,10,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-420,10,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-357,10,-280>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<300,10,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<237,10,-280>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<-60,10,-137>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<-420,10,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<-220,35,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 10, "GENERATE", "V<300,10,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 11, "GENERATE", "V<100,35,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 12, "GENERATE", "V<-420,10,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 13, "GENERATE", "V<-357,10,240>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 14, "GENERATE", "V<300,10,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 15, "GENERATE", "V<237,10,240>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 16, "GENERATE", "V<-160,35,520>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 17, "GENERATE", "V<-163,10,680>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 18, "GENERATE", "V<40,35,520>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 19, "GENERATE", "V<43,10,680>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 20, "GENERATE", "V<-60,35,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 21, "GENERATE", "V<-60,10,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 22, "GENERATE", "V<-60,10,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-60,10,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-420,10,-522>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,10,-30>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<-460,10,-295>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<340,10,-295>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 2, "GENERATE", "V<-460,10,25>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 3, "GENERATE", "V<340,10,25>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 4, "GENERATE", "V<-460,10,225>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 5, "GENERATE", "V<340,10,225>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-100,10,-175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-20,10,-175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-60,10,-320>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-340,10,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<220,10,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-180,35,520>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<60,35,520>/V<0,0,0>")
if be:FLGisOn(218) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<340,0,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<380,0,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<420,0,-440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<420,0,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<420,0,-360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<460,0,-440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<460,0,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<460,0,-360>/V<0,0,0>")
end
if be:FLGisOn(216) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-220,0,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-180,0,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-180,0,-320>/V<0,0,0>")
end
if be:FLGisOn(217) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<60,0,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<100,0,-280>/V<0,0,0>")
end
if be:FLGisOn(219) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-460,0,240>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-180,10,635>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<60,10,635>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<-60,10,-275>/V<0,0,0>")
for local_1 = 1, 8 do
    if be:FLGisOn(local_1 + 192) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(214) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<-100,10,-145>/V<0,0,0>")
end
if be:FLGisOn(215) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 1, "GENERATE", "V<-20,10,-145>/V<0,0,0>")
end
if be:FLGisOn(216) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<-245,10,-280>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d2bkwall", 0, "SQ_CUTRIGHT")
end
if be:FLGisOn(217) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<125,10,-280>/V<0,90,0>")
    be:sd("MODELCTRL", "g_d2bkwall", 1, "SQ_CUTLEFT")
end
if be:FLGisOn(218) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<315,10,-400>/V<0,-90,0>")
end
if be:FLGisOn(219) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<-435,10,240>/V<0,90,0>")
end
if be:FLGisOn(220) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<-180,10,-320>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d2door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 7, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 8, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 10, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 11, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 12, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 13, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 14, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 15, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 16, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 17, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 18, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 19, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 20, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 21, "SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 22, "SQ_CLEAR")
if be:FLGisOn(201) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(202) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 13, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
end
if be:FLGisOn(204) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 16, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 17, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
end
if be:FLGisOn(205) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 18, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 19, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT")
end
if be:FLGisOn(206) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(207) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(210) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(211) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(212) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 4, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(213) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 5, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 14, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
end
if be:FLGisOn(208) + be:FLGisOn(209) == 2 then
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
else
    be:FLGset(208, 0)
    be:FLGset(209, 0)
end
if be:FLGisOn(175) == 1 then
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(176) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    g_pharaoh02 = 1
end
if be:FLGisOn(177) + be:FLGisOn(190) + be:FLGisOn(191) + be:FLGisOn(192) == 4 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(178) == 1 then
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(180) == 1 then
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(181) == 1 then
    be:sd("MODELCTRL", "g_d2door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(184) == 1 then
    be:sd("MODELCTRL", "g_d2door", 15, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:FLGset(203, 1)
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    be:FLGset(203, 0)
end
if be:FLGisOn(188) == 1 then
    be:sd("MODELCTRL", "g_d2door", 20, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall21", 0, "OFFHIT")
end
if be:FLGisOn(189) == 1 then
    be:sd("MODELCTRL", "g_d2door", 22, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall23", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d2door", 21, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall22", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map205b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map205b3", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
