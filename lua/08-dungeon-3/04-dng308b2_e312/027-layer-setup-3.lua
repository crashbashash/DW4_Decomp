funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-140,40,-440>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-100,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<180,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<60,65,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<0,40,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<120,40,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<280,40,320>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-200,65,360>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<0,65,360>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-340,40,420>/V<0,0,0>")
if be:FLGisOn(135) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-140,30,-360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-140,30,-320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-180,30,-320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-180,30,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-140,30,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-180,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-180,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-140,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-180,30,-160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-140,30,-160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-100,30,-160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-60,30,-160>/V<0,0,0>")
else
    g_dcap = 1
end
if be:FLGisOn(136) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<420,30,-120>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-100,65,475>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-180,40,-240>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<260,40,80>/V<0,0,0>")
for local_1 = 1, 7 do
    if be:FLGisOn(local_1 + 127) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(135) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-140,40,-385>/V<0,180,0>")
end
if be:FLGisOn(136) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 1, "GENERATE", "V<395,40,-120>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d3bkwall", 1, "SQ_CUTBOTH")
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<-80,40,-440>/V<0,90,0>")
end
if be:FLGisOn(138) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 1, "GENERATE", "V<-240,40,200>/V<0,90,0>")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_CLEAR")
if be:FLGisOn(117) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(120) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(121) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(124) == 1 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(126) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(127) == 1 then
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map308b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map308b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
