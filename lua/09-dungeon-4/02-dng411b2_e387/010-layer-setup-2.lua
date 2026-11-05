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
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<280,40,-300>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<220,40,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<-340,40,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<0,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<-160,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<-240,40,-260>/V<0,90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<200,40,220>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<240,40,220>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-100,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-60,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-60,40,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<-60,40,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<-420,40,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<-420,40,-20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<-420,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<-420,40,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<320,40,200>/V<0,0,0>")
if be:FLGisOn(133) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<100,30,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<140,30,-340>/V<0,0,0>")
end
if be:FLGisOn(189) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-260,30,60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-260,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-220,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-180,30,20>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-175,40,185>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-500,40,220>/V<0,0,0>")
for local_1 = 1, 4 do
    if be:FLGisOn(local_1 + 128) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(133) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<75,40,-340>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d4bkwall", 0, "SQ_CUTLEFT")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_CLEAR")
if be:FLGisOn(117) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(119) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(121) == 1 then
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(123) == 1 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(127) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
g_security = 1
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map411b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map411b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
