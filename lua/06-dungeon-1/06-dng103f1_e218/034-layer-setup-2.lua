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
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<-380,35,-120>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<-160,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<-160,10,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<380,35,-120>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<160,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<100,10,-120>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<160,10,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<-300,10,-360>/V<0,90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-80,10,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<80,10,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-270,10,-370>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-270,10,-430>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-160,10,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<-129,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<-191,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<-160,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<-205,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<-115,10,-160>/V<0,180,0>")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-45,10,420>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<-160,10,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<160,10,355>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<0,10,-160>/V<0,45,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-125,10,395>/V<0,0,0>")
for local_2 = 1, 8 do
    if be:FLGisOn(local_2 + 112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_2))
    end
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_BUTTON")
if be:FLGisOn(121) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(122) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(107) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(109) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
else
    be:FLGset(108, 0)
end
be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map103f1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map103f1", 0, "GENERATE", "SQ_OPEN")
    end
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 and be:MDLisLive("j_mapcur", local_3) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_3, "GENERATE")
        end
    end
end
