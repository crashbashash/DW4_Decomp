funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 7 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<440,100,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<335,100,95>/V<0,90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<335,100,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 2, "GENERATE", "V<-75,100,405>/V<0,180,0>")
be:sd("MODELCTRL", "g_dtwbase", 0, "GENERATE", "V<120,100,-140>/V<0,180,0>")
be:sd("MODELCTRL", "g_dtwbase", 1, "GENERATE", "V<-320,100,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtwbase", 2, "GENERATE", "V<-320,100,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtwbase", 3, "GENERATE", "V<120,100,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtwbase", 4, "GENERATE", "V<-120,100,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtwbase", 5, "GENERATE", "V<-120,100,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<120,100,-140>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-320,100,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<-320,100,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<120,100,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 4, "GENERATE", "V<-120,100,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 5, "GENERATE", "V<-120,100,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<220,100,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<440,100,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<440,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<260,125,-260>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<260,125,300>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<-380,125,300>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<-280,125,-360>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<-260,125,-260>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 8, "GENERATE", "V<100,100,-420>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 9, "GENERATE", "V<120,100,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 10, "GENERATE", "V<-280,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 11, "GENERATE", "V<120,100,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<125,100,-135>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-325,100,-65>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<-325,100,105>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<125,100,175>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 4, "GENERATE", "V<-125,100,-65>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 5, "GENERATE", "V<-125,100,105>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmphealeffect", 0, "GENERATE", "V<180,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmpheal", 0, "GENERATE", "V<180,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 0, "GENERATE", "V<-35,100,-200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 1, "GENERATE", "V<0,100,-180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 2, "GENERATE", "V<35,100,-160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 3, "GENERATE", "V<-35,100,200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 4, "GENERATE", "V<0,100,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmovescaffold", 5, "GENERATE", "V<35,100,240>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dconvair", 0, "GENERATE", "V<-20,100,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<245,100,-15>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<245,100,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbossgate", 0, "GENERATE", "V<-150,100,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<311,100,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 1, "GENERATE", "V<311,100,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 2, "GENERATE", "V<-15,100,491>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<249,100,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 1, "GENERATE", "V<249,100,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 2, "GENERATE", "V<-15,100,429>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<280,100,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 1, "GENERATE", "V<280,100,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 2, "GENERATE", "V<-15,100,460>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<235,100,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<325,100,5>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<235,100,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<325,100,35>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<-15,100,415>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<-15,100,505>/V<0,90,0>")
if be:FLGisOn(169) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<200,90,100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<160,90,100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<160,90,140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<200,90,140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<180,95,120>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-240,125,-260>/V<0,-90,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<240,125,-260>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<240,125,300>/V<0,90,0>")
for local_1 = 1, 4 do
    if be:FLGisOn(local_1 + 159) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(169) ~= 1 then
    be:sd("MODELCTRL", "g_dtbkwall", 0, "GENERATE", "V<225,100,100>/V<0,90,0>")
    be:sd("MODELCTRL", "g_dtbkwall", 0, "SQ_CUTLEFT")
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 10, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 11, "SQ_CLEAR")
if be:FLGisOn(164) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
end
if be:FLGisOn(165) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(164) + be:FLGisOn(165) == 2 then
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(166) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw1", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall01", 0, "OFFHIT")
end
if be:FLGisOn(167) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall02", 0, "OFFHIT")
end
if be:FLGisOn(168) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw1", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton1", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall03", 0, "OFFHIT")
end
if be:FLGisOn(132) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(134) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(137) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(142) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(147) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(149) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(151) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(154) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(156) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(159) == 1 then
    be:sd("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON")
    g_bossgate = 1
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map206f2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map206f2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
