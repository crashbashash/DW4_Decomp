funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<-680,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<-680,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<380,10,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<380,10,200>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<0,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-200,10,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-580,35,240>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-480,35,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-760,10,340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-680,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<-680,10,-500>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<80,10,495>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-120,10,385>/V<0,-90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<620,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-680,10,-590>/V<0,0,0>")
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-600,0,560>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-200,10,85>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-620,10,-120>/V<0,90,0>")
for local_1 = 1, 12 do
    if be:FLGisOn(local_1 + 157) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-575,10,560>/V<0,90,0>")
    be:sd("MODELCTRL", "g_d3bkwall", 0, "SQ_CUTBOTH")
end
if be:FLGisOn(171) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<180,10,320>/V<0,-90,0>")
end
if be:FLGisOn(172) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 1, "GENERATE", "V<-700,10,440>/V<0,-90,0>")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_BOSS")
be:sd("MODELCTRL", "g_d3door", 8, "SQ_CLEAR")
if be:FLGisOn(139) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(146) == 1 then
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(147) == 1 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(150) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(153) == 1 then
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(157) == 1 then
    be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
g_security = 1
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map308b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map308b3", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
