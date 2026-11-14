local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 3 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<260,100,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<265,100,185>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<300,100,185>/V<0,180,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<240,100,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<-400,125,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<-280,100,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<-200,100,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<180,100,-280>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<340,100,-280>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<400,125,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<0,100,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 0, "GENERATE", "V<-20,100,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 1, "GENERATE", "V<20,100,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 2, "GENERATE", "V<-20,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 3, "GENERATE", "V<20,100,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 4, "GENERATE", "V<-20,100,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dskyscaffold", 5, "GENERATE", "V<20,100,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmphealeffect", 0, "GENERATE", "V<210,100,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmpheal", 0, "GENERATE", "V<210,100,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<130,100,370>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<130,100,370>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-180,100,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-220,100,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-260,100,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<165,100,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbossgate", 0, "GENERATE", "V<0,100,-30>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<240,100,209>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<240,100,271>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<240,100,240>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<240,100,195>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<240,100,285>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-240,100,-445>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<-75,100,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<-40,100,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 3, "GENERATE", "V<-5,100,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 4, "GENERATE", "V<160,100,355>/V<0,0,0>")
if be:FLGisOn(153) + be:FLGisOn(154) == 0 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<200,90,160.5>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<240,90,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<240,90,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<240,90,80>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<400,100,165>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<200,100,35>/V<0,0,0>")
for ramNo = 1, 12 do
    if be:FLGisOn(ramNo + 138) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", ramNo))
    end
end
if be:FLGisOn(153) ~= 1 then
    be:sd("MODELCTRL", "g_dtbkwall", 0, "GENERATE", "V<240,100,55>/V<0,180,0>")
    be:sd("MODELCTRL", "g_dtbkwall", 0, "SQ_CUTLEFT")
end
if be:FLGisOn(154) ~= 1 then
    be:sd("MODELCTRL", "g_dtbkwall", 1, "GENERATE", "V<200,100,185>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dtbkwall", 1, "SQ_CUTLEFT")
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_CLEAR")
if be:FLGisOn(151) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(152) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
    be:sd("HITLANDMODEL", "barrierwall01", 0, "OFFHIT")
end
if be:FLGisOn(125) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(128) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(129) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(131) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(134) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(136) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(138) == 1 then
    be:sd("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON")
    g_bossgate = 1
else
    be:FLGset(137, 0)
end
for ramNo = 0, 2 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SQ_POWERON")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map103f2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map103f2", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
