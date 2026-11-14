local local_0
mswk61094 = "TALKFONT01/font00/I<10>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-420,10,-340>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<-680,10,-200>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<-660,10,-180>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<-540,10,-100>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<-560,10,-80>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<-400,35,120>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<-200,35,120>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<-300,35,20>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<-300,35,140>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-260,10,260>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<-320,10,360>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<-200,10,360>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<-200,10,440>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 13, "GENERATE", "V<100,10,140>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 14, "GENERATE", "V<160,10,120>/V<0,90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 15, "GENERATE", "V<200,35,280>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 16, "GENERATE", "V<325,10,280>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 17, "GENERATE", "V<355,10,280>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 18, "GENERATE", "V<340,10,265>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 19, "GENERATE", "V<340,10,295>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 20, "GENERATE", "V<280,10,440>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 21, "GENERATE", "V<660,10,-580>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 22, "GENERATE", "V<660,10,-780>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 23, "GENERATE", "V<660,10,-980>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 24, "GENERATE", "V<660,10,-1180>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<-465,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<-415,10,-240>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<-625,10,75>/V<0,-45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<-535,10,75>/V<0,-135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<-605,10,95>/V<0,135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<-555,10,95>/V<0,45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 6, "GENERATE", "V<-605,10,145>/V<0,-135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 7, "GENERATE", "V<-555,10,145>/V<0,-45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 8, "GENERATE", "V<-625,10,165>/V<0,45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 9, "GENERATE", "V<-535,10,165>/V<0,135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 10, "GENERATE", "V<-600,10,100>/V<0,-45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 11, "GENERATE", "V<-560,10,100>/V<0,-135,0>")
be:sd("MODELCTRL", "g_dbarrierp", 12, "GENERATE", "V<-600,10,140>/V<0,45,0>")
be:sd("MODELCTRL", "g_dbarrierp", 13, "GENERATE", "V<-560,10,140>/V<0,135,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<-451,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<-429,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw8", 0, "GENERATE", "V<-580,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw9", 0, "GENERATE", "V<-580,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw9", 1, "GENERATE", "V<-580,10,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-660,10,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-660,10,-165>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-575,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-540,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<-615,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 5, "GENERATE", "V<-580,10,85>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 6, "GENERATE", "V<-300,10,165>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 7, "GENERATE", "V<100,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 8, "GENERATE", "V<305,10,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 9, "GENERATE", "V<340,10,245>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-380,10,390>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-420,10,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-380,10,450>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<660,10,-520>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<660,10,-520>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<-540,10,-325>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<-625,10,0>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlasergun", 2, "GENERATE", "V<-75,10,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dlasergun", 3, "GENERATE", "V<-40,10,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 4, "GENERATE", "V<-75,10,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dlasergun", 5, "GENERATE", "V<-5,10,140>/V<0,180,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<660,10,-1270>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<20,10,25>/V<0,180,0>")
for ramNo = 1, 28 do
    if be:FLGisOn(ramNo + 208) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", ramNo))
    end
end
if be:FLGisOn(247) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<20,10,65>/V<0,0,0>/SQ_CUTRIGHT")
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<20,0,40>/V<0,0,0>")
end
if be:FLGisOn(248) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<-460,10,20>/V<0,90,0>")
end
if be:FLGisOn(249) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-160,35,120>/V<0,90,0>")
end
if be:FLGisOn(188) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(195) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(196) == 1 then
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(198) == 1 then
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(201) == 1 then
    be:sd("MODELCTRL", "g_d4door", 15, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
end
if be:FLGisOn(203) == 1 then
    be:sd("MODELCTRL", "g_d4door", 20, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall21", 0, "OFFHIT")
end
if be:FLGisOn(208) == 1 then
    be:sd("MODELCTRL", "g_d4door", 22, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall23", 0, "OFFHIT")
end
if be:FLGisOn(250) == 1 then
    be:sd("MODELCTRL", "g_d4door", 23, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall24", 0, "OFFHIT")
end
if be:FLGisOn(251) == 1 then
    be:sd("MODELCTRL", "g_d4door", 24, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall25", 0, "OFFHIT")
end
if be:FLGisOn(237) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
end
if be:FLGisOn(238) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    if be:FLGisOn(237) == 1 then
        be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
end
if be:FLGisOn(239) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    if be:FLGisOn(240) == 1 then
        be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
end
if be:FLGisOn(240) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
end
if be:FLGisOn(241) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall3", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw9", 1, "SQ_POWERON")
end
if be:FLGisOn(242) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall4", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw9", 0, "SQ_POWERON")
end
if be:FLGisOn(241) ~= 1 then
    if be:FLGisOn(242) == 1 then
    end
end
be:sd("MODELCTRL", "g_dbarrierp", 10, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 11, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 12, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 13, "SQ_POWERON")
if be:FLGisOn(243) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 6, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 6, "SQ_POWERON")
end
if be:FLGisOn(244) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 7, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 7, "SQ_POWERON")
end
if be:FLGisOn(246) == 1 and be:FLGisOn(244) == 1 then
    g_door15 = 1
else
    be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
end
if be:FLGisOn(245) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 8, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 16, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 17, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 8, "SQ_POWERON")
end
if be:FLGisOn(246) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 9, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 18, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 19, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 9, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 21, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall22", 0, "OFFHIT")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw8", 0, "SQ_POWERON")
for ramNo = 0, 9 do
    be:sd("MODELCTRL", "g_dbarrierp", ramNo, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("HITLANDMODEL", "safewall0", 0, "OFFHIT")
be:sd("HITLANDMODEL", "safewall1", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
