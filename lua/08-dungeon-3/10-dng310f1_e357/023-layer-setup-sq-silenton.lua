local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 310
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for ramNo = 100, 299 do
        be:FLGset(ramNo, 0)
    end
end
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<-325,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<-235,10,315>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<235,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<325,10,315>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<-325,10,-355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<-235,10,-355>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<-280,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 1, "GENERATE", "V<280,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 2, "GENERATE", "V<-280,10,-355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<-311,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 1, "GENERATE", "V<249,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 2, "GENERATE", "V<-311,10,-355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<-249,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 1, "GENERATE", "V<311,10,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 2, "GENERATE", "V<-249,10,-355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-310,10,330>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-310,10,-370>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 0, "GENERATE", "V<-160,10,340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 1, "GENERATE", "V<160,10,340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 2, "GENERATE", "V<-440,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 3, "GENERATE", "V<160,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 4, "GENERATE", "V<440,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 5, "GENERATE", "V<440,10,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<-100,10,340>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<100,10,340>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<-340,10,260>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<-380,35,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<160,10,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<260,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<320,10,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<-100,35,-420>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 8, "GENERATE", "V<100,35,-420>/V<0,90,0>")
be:sd("MODELCTRL", "g_dtdoor", 9, "GENERATE", "V<-340,10,-300>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-310,10,-335>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<245,10,-305>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<245,10,265>/V<0,0,0>")
for ramNo = 1, 22 do
    if be:FLGisOn(ramNo + 106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", ramNo))
    end
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_BUTTON")
if be:FLGisOn(129) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(130) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(100) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(102) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(104) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
for ramNo = 0, 2 do
    be:sd("MODELCTRL", "g_dbarrierw1", ramNo, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", ramNo, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", ramNo, "SQ_POWERON")
end
for ramNo = 0, 5 do
    be:sd("MODELCTRL", "g_dbarrierp", ramNo, "SQ_POWERON")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map310f1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map310f1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
