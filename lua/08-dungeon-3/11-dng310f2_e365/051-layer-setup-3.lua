funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 12 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<0,40,-545>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<0,40,-485>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<-85,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<-5,40,-480>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<5,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<85,40,-480>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 6, "GENERATE", "V<0,40,-475>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 7, "GENERATE", "V<0,40,-415>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 8, "GENERATE", "V<-375,40,-105>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 9, "GENERATE", "V<-375,40,-15>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 10, "GENERATE", "V<-345,40,-105>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 11, "GENERATE", "V<-345,40,-15>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<-375,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 1, "GENERATE", "V<-345,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<-71,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 1, "GENERATE", "V<19,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 2, "GENERATE", "V<-375,40,-91>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 3, "GENERATE", "V<-345,40,-91>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<-19,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 1, "GENERATE", "V<71,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 2, "GENERATE", "V<-375,40,-29>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 3, "GENERATE", "V<-345,40,-29>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw4", 0, "GENERATE", "V<-45,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw4", 1, "GENERATE", "V<45,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw5", 0, "GENERATE", "V<0,40,-515>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw5", 1, "GENERATE", "V<0,40,-445>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-15,40,-465>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<15,40,-495>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-330,40,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-390,40,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 0, "GENERATE", "V<-200,40,345>/V<0,0,0>")
be:sd("MODELCTRL", "g_drolllaser", 0, "GENERATE", "V<0,40,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_drolllsbase", 0, "GENERATE", "V<0,40,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<-360,40,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<-360,40,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<0,40,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<240,65,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<400,65,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<300,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<0,40,380>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3movecell1", 0, "GENERATE", "V<0,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3movecell1w", 0, "GENERATE", "V<0,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<15,40,-465>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<35,40,-15>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<400,40,60>/V<0,0,0>")
if be:FLGisOn(143) ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GBOX-01")
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
if be:FLGisOn(133) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(134) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(136) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(144) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw4", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall03", 0, "OFFHIT")
end
if be:FLGisOn(145) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw4", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall02", 0, "OFFHIT")
end
if be:FLGisOn(146) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw1", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(147) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 8, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 9, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(148) ~= 1 then
    be:sd("HITLANDMODEL", "cell01right", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_d3movecell1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3movecell1w", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "cell01left", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dbarrierw5", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw5", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 6, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 7, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map310f2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map310f2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 and be:MDLisLive("j_mapcur", local_1) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_1, "GENERATE")
        end
    end
end
